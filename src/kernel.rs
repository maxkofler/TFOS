#![no_std]
#![no_main]
#![allow(dead_code)]

use core::fmt::Write;

use monnos::{
    drivers::uart::{BlockingUART, COM_BASE},
    interrupts,
};

pub mod monnos;

fn get_first_uart() -> Option<(usize, BlockingUART)> {
    for (num, base) in COM_BASE.iter().enumerate() {
        if let Some(uart) = BlockingUART::new(*base) {
            return Some((num, uart));
        }
    }

    None
}

#[no_mangle]
extern "C" fn kernel_entry(_pos_multiboot_info: u32) -> ! {
    let (com_num, mut serial) = get_first_uart().expect("Some working UART");

    writeln!(serial, "Primary UART: COM{com_num}").unwrap();

    for (num, base) in COM_BASE.iter().enumerate() {
        if BlockingUART::new(*base).is_some() {
            writeln!(serial, "Found working UART COM{num}").unwrap();
        }
    }

    writeln!(serial, "Enabling interrupts...").unwrap();

    interrupts::enable_interrupts();

    writeln!(serial, "MONNOS is ready!").unwrap();

    loop {}
}
