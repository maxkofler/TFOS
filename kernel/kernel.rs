#![no_std]
#![no_main]
#[panic_handler]
pub fn panic(_: &core::panic::PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
extern "C" fn kernel_main() -> ! {
    // For now, we just call through to the old C kernel main
    unsafe {
        kernel_main_c();
    }

    // Make sure we don't return from here
    loop {}
}

extern "C" {
    fn kernel_main_c();
}
