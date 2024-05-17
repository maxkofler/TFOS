#![no_std]
#![no_main]
#![allow(dead_code)]

use core::panic::PanicInfo;

mod monnos;

#[no_mangle]
fn kernel_entry() -> ! {
    let port: u16 = 0x3f8;

    let string = "MONNOS";
    for c in string.bytes() {
        monnos::io::port::out8(port, c).unwrap();
    }

    loop {}
}

#[inline(never)]
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
