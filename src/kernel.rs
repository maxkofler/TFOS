#![no_std]
#![no_main]
#![allow(dead_code)]

use core::panic::PanicInfo;

mod monnos;

#[no_mangle]
extern "C" fn kernel_entry(multiboot_info: u32) -> ! {
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
