// disable rust standard library
#![no_std]
// disables Rust runtime init,
#![no_main]

use core::panic::PanicInfo;

#[inline(never)]
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
