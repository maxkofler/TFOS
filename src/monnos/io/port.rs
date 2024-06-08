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

/// Changes a single bit in at `port` by reading it and setting `bit` at `pos`
/// # Arguments
/// * `port` - The port to act on
/// * `pos` - The position of the bit to manipulate
/// * `bit` - The bit to set or unset
pub fn out8_bit(port: u16, pos: u8, bit: bool) -> Result<(), PortIOError> {
    let byte = in8(port)? | 1 << pos;
    out8(port, byte & ((bit as u8) << pos))
}

/// Output two bytes to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out16(port: u16, data: u16) -> Result<(), PortIOError> {
    Ok(asm::out16(port, data))
}

/// Changes a single bit in at `port` by reading it and setting `bit` at `pos`
/// # Arguments
/// * `port` - The port to act on
/// * `pos` - The position of the bit to manipulate
/// * `bit` - The bit to set or unset
pub fn out16_bit(port: u16, pos: u8, bit: bool) -> Result<(), PortIOError> {
    let byte = in16(port)? | 1 << pos;
    out16(port, byte & ((bit as u16) << pos))
}

/// Output four bytes to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out32(port: u16, data: u32) -> Result<(), PortIOError> {
    Ok(asm::out32(port, data))
}

/// Changes a single bit in at `port` by reading it and setting `bit` at `pos`
/// # Arguments
/// * `port` - The port to act on
/// * `pos` - The position of the bit to manipulate
/// * `bit` - The bit to set or unset
pub fn out32_bit(port: u16, pos: u8, bit: bool) -> Result<(), PortIOError> {
    let byte = in32(port)? | 1 << pos;
    out32(port, byte & ((bit as u32) << pos))
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
