/// Registers file provided by an interrupt call
#[repr(C, align(4))]
pub struct RegistersX86 {
    pub ds: u32,

    pub edi: u32,
    pub esi: u32,
    pub ebp: u32,
    pub esp: u32,
    pub ebx: u32,
    pub edx: u32,
    pub ecx: u32,
    pub eax: u32,

    pub eip: u32,
    pub cs: u32,
    pub eflags: u32,
    pub eseresp: u32,
    pub ss: u32,
}
