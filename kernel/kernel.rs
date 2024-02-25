#![no_std]
#![no_main]

mod monnos;

#[panic_handler]
pub fn panic(_: &core::panic::PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
extern "C" fn kernel_main() -> ! {
    // Make sure we don't return from here
    loop {}
}
