use crate::monnos::asm;

#[derive(Debug)]
/// A port IO error
pub struct PortIOError {}

/// Output a byte to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out8(port: u16, data: u8) -> Result<(), PortIOError> {
    Ok(asm::out8(port, data))
}

/// Output two bytes to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out16(port: u16, data: u16) -> Result<(), PortIOError> {
    Ok(asm::out16(port, data))
}

/// Output four bytes to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out32(port: u16, data: u32) -> Result<(), PortIOError> {
    Ok(asm::out32(port, data))
}

/// Receive one byte from the IO port of the CPU
/// * `port` - The port to receive from
pub fn in8(port: u16) -> Result<u8, PortIOError> {
    Ok(asm::in8(port))
}

/// Receive two bytes from the IO port of the CPU
/// * `port` - The port to receive from
pub fn in16(port: u16) -> Result<u16, PortIOError> {
    Ok(asm::in16(port))
}

/// Receive four bytes from the IO port of the CPU
/// * `port` - The port to receive from
pub fn in32(port: u16) -> Result<u32, PortIOError> {
    Ok(asm::in32(port))
}
