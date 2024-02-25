#![no_std]
#![no_main]
use no_panic::no_panic;

mod monnos;

#[panic_handler]
pub fn panic(_: &core::panic::PanicInfo) -> ! {
    loop {}
}

/// This is the main kernel entry point. We should not return from this.
/// Additionally, this is marked no_panic, so maximum safety is guaranteed.
#[no_panic]
fn kernel_run() {}

#[no_mangle]
pub extern "C" fn kernel_main() {
    kernel_run();

    // Make sure we don't return from here
    loop {}
}
