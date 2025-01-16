/// The header structure for a normal PCI device
/// (Header type = `0x00`)
#[repr(C, align(1))]
#[derive(Debug, Clone)]
pub struct PCIDeviceHeader {
    /// The vendor id for the PCI device
    pub vendor_id: u16,
    /// The device id assigned by the vendor
    pub device_id: u16,

    /// The PCI command register
    pub command: u16,
    /// The PCI status register
    pub status: u16,

    /// The revision of the device
    pub revision_id: u8,
    /// The programming interface to use for this device
    pub programming_interface: u8,
    /// The subclass of the device
    pub subclass: u8,
    /// The class of the device
    pub class: u8,

    /// The cache line size of the PCI device in 32 bit units
    pub cache_line_size: u8,
    pub latency_timer: u8,
    /// The type of the following header (Here `0x00`)
    pub header_type: u8,
    /// The Built In Self Test register
    pub bist: u8,

    /// The 6 Base Address Registers
    pub bars: [u32; 6],

    /// The Cardbus Card Information Structure register
    pub cis_ptr: u32,

    pub subsystem_vendor_id: u16,
    pub subsystem_id: u16,

    pub expansion_rom_base: u32,

    pub capabilities_ptr: u8,

    reserved_1: u8,
    reserved_2: u16,
    reserved_3: u32,

    pub interrupt_line: u8,
    pub interrupt_pin: u8,
    pub min_grant: u8,
    pub max_latency: u8,
}
