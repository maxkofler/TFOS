use crate::monnos::asm;

/// Output a byte to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out8(port: u16, data: u8) {
    unsafe { asm::asm_out8(port, data) }
}

/// Changes a single bit in at `port` by reading it and setting `bit` at `pos`
/// # Arguments
/// * `port` - The port to act on
/// * `pos` - The position of the bit to manipulate
/// * `bit` - The bit to set or unset
pub fn out8_bit(port: u16, pos: u8, bit: bool) {
    let byte = in8(port) | 1 << pos;
    out8(port, byte & ((bit as u8) << pos))
}

/// Output two bytes to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out16(port: u16, data: u16) {
    unsafe { asm::asm_out16(port, data) }
}

/// Changes a single bit in at `port` by reading it and setting `bit` at `pos`
/// # Arguments
/// * `port` - The port to act on
/// * `pos` - The position of the bit to manipulate
/// * `bit` - The bit to set or unset
pub fn out16_bit(port: u16, pos: u8, bit: bool) {
    let byte = in16(port) | 1 << pos;
    out16(port, byte & ((bit as u16) << pos))
}

/// Output four bytes to the IO port of the CPU
/// * `port` - The port to output to
/// * `data` - The data to output
pub fn out32(port: u16, data: u32) {
    unsafe { asm::asm_out32(port, data) }
}

/// Changes a single bit in at `port` by reading it and setting `bit` at `pos`
/// # Arguments
/// * `port` - The port to act on
/// * `pos` - The position of the bit to manipulate
/// * `bit` - The bit to set or unset
pub fn out32_bit(port: u16, pos: u8, bit: bool) {
    let byte = in32(port) | 1 << pos;
    out32(port, byte & ((bit as u32) << pos))
}

/// Receive one byte from the IO port of the CPU
/// * `port` - The port to receive from
pub fn in8(port: u16) -> u8 {
    unsafe { asm::asm_in8(port) }
}

/// Receive two bytes from the IO port of the CPU
/// * `port` - The port to receive from
pub fn in16(port: u16) -> u16 {
    unsafe { asm::asm_in16(port) }
}

/// Receive four bytes from the IO port of the CPU
/// * `port` - The port to receive from
pub fn in32(port: u16) -> u32 {
    unsafe { asm::asm_in32(port) }
}
