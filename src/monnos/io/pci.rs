//! Functions for interfacing with PCI
use super::port::{in32, out32};

/// The `config` port for the PCI configuration space
const PORT_CFG_ADDR: u16 = 0xCF8;
/// The `data` port for the PCI configuration space
const PORT_CFG_DATA: u16 = 0xCFC;

/// Reads a configuration space register using the I/O ports of the CPU
/// # Arguments
/// * `bus` - The bus to read from
/// * `device` - The device to read from (4 bits)
/// * `function` - The function to read from (4 bits)
/// * `register_offset` - The [4 byte aligned] register offset
pub fn config_io_read_register(bus: u8, device: u8, function: u8, register_offset: u8) -> u32 {
    let addr_data: u32 = 1 << 31
        | ((bus as u32) << 16)
        | ((device as u32 & 0b1111) << 11)
        | ((function as u32 & 0b1111) << 8)
        | (register_offset as u32 & 0b11111100);

    out32(PORT_CFG_ADDR, addr_data);

    in32(PORT_CFG_DATA)
}

/// Reads `N` consecutive 32 bit registers from PCI configuration space using the CPU I/O ports
/// # Argumets
/// * `bus` - The bus to read from
/// * `device` - The device to read from (4 bits)
/// * `function` - The function to read from (4 bits)
pub fn config_io_read_registers<const N: usize>(bus: u8, device: u8, function: u8) -> [u32; N] {
    let mut data = [0u32; N];

    for i in 0..N {
        data[i] = config_io_read_register(bus, device, function, i as u8 * 4);
    }

    data
}
