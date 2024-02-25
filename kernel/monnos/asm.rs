use core::arch::asm;

#[inline(always)]
pub fn out8(port: u16, data: u8) {
    unsafe { asm!("out dx, al", in("dx")port, in("al")data) }
}

#[inline(always)]
pub fn out16(port: u16, data: u16) {
    unsafe { asm!("out dx, ax", in("dx")port, in("ax")data) }
}

#[inline(always)]
pub fn out32(port: u16, data: u32) {
    unsafe { asm!("out dx, eax", in("dx")port, in("eax")data) }
}

#[inline(always)]
pub fn in8(port: u16) -> u8 {
    let mut data: u8;
    unsafe { asm!("in al, dx", out("al")data, in("dx")port) }
    data
}

#[inline(always)]
pub fn in16(port: u16) -> u16 {
    let mut data: u16;
    unsafe { asm!("in ax, dx", out("ax")data, in("dx")port) }
    data
}

#[inline(always)]
pub fn in32(port: u16) -> u32 {
    let mut data: u32;
    unsafe { asm!("in eax, dx", out("eax")data, in("dx")port) }
    data
}
