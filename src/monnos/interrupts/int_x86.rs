use core::{array, mem::size_of, ptr::addr_of};

use x86::{dtables::DescriptorTablePointer, irq, segmentation::SegmentSelector, Ring};

use crate::monnos::{arch::RegistersX86, io::port::out8, panic::kernel_panic};

/// The global Interrupt Descriptor Table
static mut IDT_X86: [IDTGate32Raw; 0xFF] = [IDTGate32Raw {
    offset_low: 0,
    segment_selector: 0,
    zero: 0,
    attributes: 0,
    offset_high: 0,
}; 0xFF];

/// The length of the IDT on X86
pub const DEFAULT_IDT_LEN_X86: usize = 58;

/// Pointers to interrupt service routines
static mut ISRS: [Option<&dyn Fn(InterruptPayload)>; 32] = [None; 32];
/// Pointers to interrupt request routines
static mut IRQS: [Option<&dyn Fn(InterruptPayload)>; 16] = [None; 16];

/// An ISR guard that automatically returns
/// the previous ISR in the IDT
pub struct ISRGuard {
    entry: &'static mut Option<&'static dyn Fn(InterruptPayload)>,
    old_function: Option<&'static dyn Fn(InterruptPayload)>,
}

impl Drop for ISRGuard {
    fn drop(&mut self) {
        *self.entry = self.old_function;
    }
}

impl ISRGuard {
    /// Registers a new ISR
    /// # Arguments
    /// * `entry` - The entry to manipulate
    /// * `function` - The new function to register
    fn register<'a>(
        entry: &'static mut Option<&'static dyn Fn(InterruptPayload)>,
        function: &'a dyn Fn(InterruptPayload),
    ) -> Self {
        let old_function = *entry;

        *entry = Some(unsafe { core::mem::transmute(function) });

        Self {
            entry,
            old_function,
        }
    }
}

/// Registers a new ISR
/// # Arguments
/// * `pos` - The position to register the interrupt at
/// * `function` - The function to register at this position
pub fn register_isr_x86<'a>(
    pos: usize,
    function: &'a dyn Fn(InterruptPayload),
) -> Result<ISRGuard, ()> {
    if pos > unsafe { ISRS.len() } {
        return Err(());
    }

    let entry = unsafe { &mut ISRS[pos] };

    Ok(ISRGuard::register(entry, function))
}

/// Registers a new IRQ
/// # Arguments
/// * `pos` - The position to register the interrupt at
/// * `function` - The function to register at this position
pub fn register_irq_x86<'a>(
    pos: usize,
    function: &'a dyn Fn(InterruptPayload),
) -> Result<ISRGuard, ()> {
    if pos > unsafe { IRQS.len() } {
        return Err(());
    }

    let entry = unsafe { &mut IRQS[pos] };

    Ok(ISRGuard::register(entry, function))
}

/// An abstraction over the interrupt payload
/// that is provided by the CPU
pub struct InterruptPayload {
    /// The registers as they were at interrupt invocation
    pub registers: RegistersX86,
    /// The index of the interrupt in the IDT
    pub int_no: u32,
}
impl From<&CInterruptPayload> for InterruptPayload {
    fn from(value: &CInterruptPayload) -> Self {
        Self {
            registers: RegistersX86 {
                ds: value.ds,
                edi: value.edi,
                esi: value.esi,
                ebp: value.ebp,
                esp: value.esp,
                ebx: value.ebx,
                edx: value.edx,
                ecx: value.ecx,
                eax: value.eax,
                eip: value.eip,
                cs: value.cs,
                eflags: value.eflags,
                eseresp: value.eseresp,
                ss: value.ss,
            },
            int_no: value.int_no,
        }
    }
}

/// A raw interrupt payload as pushed by the common
/// ISR stub to be further processed
#[repr(C, align(4))]
#[derive(Debug)]
struct CInterruptPayload {
    pub ds: u32,

    pub edi: u32,
    pub esi: u32,
    pub ebp: u32,
    pub esp: u32,
    pub ebx: u32,
    pub edx: u32,
    pub ecx: u32,
    pub eax: u32,

    /// The id of the interrupt that was raised
    pub int_no: u32,
    /// The error code in the interrupt
    pub err_code: u32,

    pub eip: u32,
    pub cs: u32,
    pub eflags: u32,
    pub eseresp: u32,
    pub ss: u32,
}

/// A 32 bit gate in the Interrupt Descriptor Table
#[derive(Debug, Clone, Copy)]
#[repr(C, packed)]
struct IDTGate32Raw {
    /// The lower 16 bits of the ISR routine
    offset_low: u16,
    /// The code segment selector to use when calling
    /// the ISR
    segment_selector: u16,
    /// Reserved data - always 0
    zero: u8,
    /// Attributes to describe the ISR
    attributes: u8,
    /// The upper 16 bits of the ISR routine
    offset_high: u16,
}

impl From<IDTGateX86> for IDTGate32Raw {
    fn from(value: IDTGateX86) -> Self {
        Self {
            offset_low: value.offset as u16 & 0xFFFF,
            segment_selector: value.segment_selector.bits(),
            zero: 0,
            attributes: (1 << 7 | (value.ring as u8) << 5 | (value.ty as u8)),
            offset_high: (value.offset >> 16) as u16 & 0xFFFF,
        }
    }
}

/// Loads the interrupt descriptor table on a X86 CPU
pub fn load_idt_x86<const N: usize>(idt: &IDTX86<N>) {
    let gates = idt.gates();

    for i in 0..gates.len() {
        unsafe { IDT_X86[i] = gates[i].clone().into() }
    }

    let lidt_ptr = unsafe {
        DescriptorTablePointer {
            limit: (size_of::<IDTGate32Raw>() * gates.len()) as u16,
            base: addr_of!(IDT_X86) as *const u32,
        }
    };

    unsafe { x86::dtables::lidt(&lidt_ptr) };
}

#[no_mangle]
extern "C" fn isr_handler(payload: &CInterruptPayload) {
    // Try to find the appropriate IRQ handler
    if (payload.int_no) as usize > unsafe { ISRS.len() } {
        kernel_panic("ISR num exceeds max number of supported ISRs");
    }

    let isr = unsafe { &ISRS[payload.int_no as usize] };
    if let Some(isr) = isr {
        isr(payload.into())
    }
}

#[no_mangle]
extern "C" fn irq_handler(payload: &CInterruptPayload) {
    let num_isrs = unsafe { ISRS.len() as u32 };

    // All interrupts below 17 are traps which we can't recover from
    if payload.int_no < num_isrs {
        kernel_panic("CPU threw a TRAP exception")
    }

    let irq_num = payload.int_no - num_isrs;

    // Try to find the appropriate IRQ handler
    if irq_num as usize > unsafe { IRQS.len() } {
        kernel_panic("IRQ num exceeds max number of supported IRQs");
    }

    let irq = unsafe { &IRQS[irq_num as usize] };

    if let Some(irq) = irq {
        irq(payload.into())
    }

    // Tell the PICs that we have handled the interrupt
    if payload.int_no > 40 {
        out8(PIC2_CMD, 0x20);
    }
    out8(PIC1_CMD, 0x20);
}

extern "C" {
    fn isr0();
    fn isr1();
    fn isr2();
    fn isr3();
    fn isr4();
    fn isr5();
    fn isr6();
    fn isr7();
    fn isr8();
    fn isr9();
    fn isr10();
    fn isr11();
    fn isr12();
    fn isr13();
    fn isr14();
    fn isr15();
    fn isr16();
    fn isr17();
    fn isr18();
    fn isr19();
    fn isr20();
    fn isr21();
    fn isr22();
    fn isr23();
    fn isr24();
    fn isr25();
    fn isr26();
    fn isr27();
    fn isr28();
    fn isr29();
    fn isr30();
    fn isr31();

    fn irq0();
    fn irq1();
    fn irq2();
    fn irq3();
    fn irq4();
    fn irq5();
    fn irq6();
    fn irq7();

    fn irq8();
    fn irq9();
    fn irq10();
    fn irq11();
    fn irq12();
    fn irq13();
    fn irq14();
    fn irq15();
}

/// A gate in the X86 IDT
#[derive(Debug, Clone)]
pub struct IDTGateX86 {
    /// The offset to the ISR routine
    pub offset: u32,
    /// The segment selector to use for executing the ISR
    pub segment_selector: SegmentSelector,
    /// The type of interrupt gate
    pub ty: IDTGate32Type,
    /// The privilege ring this interrupt should be callable from
    pub ring: Ring,
}

impl IDTGateX86 {
    /// Creates a new empty IDT gate
    pub fn new_empty() -> Self {
        Self {
            offset: 0,
            segment_selector: SegmentSelector::from_raw(0),
            ty: IDTGate32Type::Task,
            ring: Ring::Ring0,
        }
    }
}

/// The possible types of IDT gates on X86
#[repr(u8)]
#[derive(Debug, Clone)]
pub enum IDTGate32Type {
    Task = 0x05,
    Interrupt16 = 0x06,
    Trap16 = 0x07,
    Interrupt32 = 0x0e,
    Trap32 = 0x0f,
}

/// An interrupt descriptor table on X86
pub struct IDTX86<const N: usize> {
    gates: [IDTGateX86; N],
    isrs: [Option<fn(&RegistersX86) -> ()>; N],
}

impl<const N: usize> IDTX86<N> {
    /// Creates a new and empty X86 IDT
    pub fn new_empty() -> Self {
        Self {
            gates: array::from_fn(|_| IDTGateX86::new_empty()),
            isrs: [None; N],
        }
    }

    /// Returns a reference to the gates array
    pub fn gates(&self) -> &[IDTGateX86] {
        &self.gates
    }

    /// Sets a function in the IDT
    /// # Arguments
    /// * `pos` - The position in the IDT
    /// * `function` - The function to be called on an interrupt
    /// * `segment_selector` - The segment selector to use for the ISR
    /// * `ring` - The ring the interrupt can be called from
    pub fn set_gate_fn32(
        &mut self,
        pos: usize,
        function: *const (),
        segment_selector: SegmentSelector,
        ring: Ring,
    ) {
        self.gates[pos] = IDTGateX86 {
            offset: function as u32,
            segment_selector,
            ty: IDTGate32Type::Interrupt32,
            ring,
        };
    }

    /// Registers the default ISR handlers for a X86 IDT
    /// # Arguments
    /// * `segment_selector` - The segment selector to use for the ISRs
    /// * `ring` - The ring the interrupt can be called from
    pub fn fill_default_isrs(&mut self, segment_selector: SegmentSelector, ring: Ring) {
        self.set_gate_fn32(0, isr0 as *const (), segment_selector, ring);
        self.set_gate_fn32(1, isr1 as *const (), segment_selector, ring);
        self.set_gate_fn32(2, isr2 as *const (), segment_selector, ring);
        self.set_gate_fn32(3, isr3 as *const (), segment_selector, ring);
        self.set_gate_fn32(4, isr4 as *const (), segment_selector, ring);
        self.set_gate_fn32(5, isr5 as *const (), segment_selector, ring);
        self.set_gate_fn32(6, isr6 as *const (), segment_selector, ring);
        self.set_gate_fn32(7, isr7 as *const (), segment_selector, ring);
        self.set_gate_fn32(8, isr8 as *const (), segment_selector, ring);
        self.set_gate_fn32(9, isr9 as *const (), segment_selector, ring);

        self.set_gate_fn32(10, isr10 as *const (), segment_selector, ring);
        self.set_gate_fn32(11, isr11 as *const (), segment_selector, ring);
        self.set_gate_fn32(12, isr12 as *const (), segment_selector, ring);
        self.set_gate_fn32(13, isr13 as *const (), segment_selector, ring);
        self.set_gate_fn32(14, isr14 as *const (), segment_selector, ring);
        self.set_gate_fn32(15, isr15 as *const (), segment_selector, ring);
        self.set_gate_fn32(16, isr16 as *const (), segment_selector, ring);
        self.set_gate_fn32(17, isr17 as *const (), segment_selector, ring);
        self.set_gate_fn32(18, isr18 as *const (), segment_selector, ring);
        self.set_gate_fn32(19, isr19 as *const (), segment_selector, ring);
        self.set_gate_fn32(20, isr20 as *const (), segment_selector, ring);
        self.set_gate_fn32(21, isr21 as *const (), segment_selector, ring);
        self.set_gate_fn32(22, isr22 as *const (), segment_selector, ring);
        self.set_gate_fn32(23, isr23 as *const (), segment_selector, ring);
        self.set_gate_fn32(24, isr24 as *const (), segment_selector, ring);
        self.set_gate_fn32(25, isr25 as *const (), segment_selector, ring);
        self.set_gate_fn32(26, isr26 as *const (), segment_selector, ring);
        self.set_gate_fn32(27, isr27 as *const (), segment_selector, ring);
        self.set_gate_fn32(28, isr28 as *const (), segment_selector, ring);
        self.set_gate_fn32(29, isr29 as *const (), segment_selector, ring);

        self.set_gate_fn32(30, isr30 as *const (), segment_selector, ring);
        self.set_gate_fn32(31, isr31 as *const (), segment_selector, ring);

        self.set_gate_fn32(32, irq0 as *const (), segment_selector, ring);
        self.set_gate_fn32(33, irq1 as *const (), segment_selector, ring);
        self.set_gate_fn32(34, irq2 as *const (), segment_selector, ring);
        self.set_gate_fn32(35, irq3 as *const (), segment_selector, ring);
        self.set_gate_fn32(36, irq4 as *const (), segment_selector, ring);
        self.set_gate_fn32(37, irq5 as *const (), segment_selector, ring);
        self.set_gate_fn32(38, irq6 as *const (), segment_selector, ring);
        self.set_gate_fn32(39, irq7 as *const (), segment_selector, ring);

        self.set_gate_fn32(40, irq8 as *const (), segment_selector, ring);
        self.set_gate_fn32(41, irq9 as *const (), segment_selector, ring);
        self.set_gate_fn32(42, irq10 as *const (), segment_selector, ring);
        self.set_gate_fn32(43, irq11 as *const (), segment_selector, ring);
        self.set_gate_fn32(44, irq12 as *const (), segment_selector, ring);
        self.set_gate_fn32(45, irq13 as *const (), segment_selector, ring);
        self.set_gate_fn32(46, irq14 as *const (), segment_selector, ring);
        self.set_gate_fn32(47, irq15 as *const (), segment_selector, ring);
    }
}

const PIC1_CMD: u16 = 0x20;
const PIC1_DATA: u16 = 0x21;

const PIC2_CMD: u16 = 0xA0;
const PIC2_DATA: u16 = 0xA1;

/// Remaps the PICs on an X86 machine
/// to work in protected mode
pub fn remap_pics_x86() {
    // Put both PICs into programming mode
    out8(PIC1_CMD, 0x11);
    out8(PIC2_CMD, 0x11);

    // Set the PIC IDT offsets
    out8(PIC1_DATA, 32); // PIC 1 IRQs start at int #32
    out8(PIC2_DATA, 40); // PIC 2 IRQs start at int #40

    out8(PIC1_DATA, 0x04); // PIC 1 accepts interrupts from PIC 2
    out8(PIC2_DATA, 0x02); // PIC 2 is a secondary PIC

    // Both PICs are in 8086 mode
    out8(PIC1_DATA, 0x01);
    out8(PIC2_DATA, 0x01);

    // We're done
    out8(PIC1_DATA, 0);
    out8(PIC2_DATA, 0);
}

/// Enables and configures the interrupt subsystem
/// for an x86 CPU
pub fn enable_interrupts_x86() {
    remap_pics_x86();

    let mut idt: IDTX86<DEFAULT_IDT_LEN_X86> = IDTX86::new_empty();
    idt.fill_default_isrs(SegmentSelector::from_raw(0x8), Ring::Ring0);

    load_idt_x86(&idt);

    unsafe { irq::enable() };
}
