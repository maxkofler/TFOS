// disable rust standard library
#![no_std]
// disables Rust runtime init,
#![no_main]

use core::panic::PanicInfo;

#[no_mangle]
fn kernel_entry() -> ! {
    loop {}
}

#[inline(never)]
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
