use core::{fmt::Write, panic::PanicInfo};

use super::drivers::uart::{BlockingUART, COM_BASE};

/// Panics the kernel due to some irrecoverable error
pub fn kernel_panic(message: &str) -> ! {
    panic!("{}", message);
}

#[inline(never)]
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    // We expect COM0 to work in any case
    let mut uart = unsafe { BlockingUART::new_unchecked(COM_BASE[0]) };

    // Try to get out the panic message, else we're doomed
    let _ = writeln!(uart, "MONNOS panicked: {}", info);

    loop {}
}
