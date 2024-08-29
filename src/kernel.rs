#![no_std]
#![no_main]
#![allow(dead_code)]
#![feature(sync_unsafe_cell)]

use log::{debug, info, Level, LevelFilter};
use monnos::{
    drivers::uart::{BlockingUART, COM_BASE},
    interrupts,
    log::MONNOSLogger,
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
    let (_com_num, uart) = get_first_uart().expect("Some working UART");

    let logger = MONNOSLogger::new(uart, Level::Trace);
    let logger: &'static MONNOSLogger = unsafe { core::mem::transmute(&logger) };

    log::set_logger(logger)
        .map(|()| log::set_max_level(LevelFilter::Trace))
        .expect("Setup logger");

    for (num, base) in COM_BASE.iter().enumerate() {
        if BlockingUART::new(*base).is_some() {
            debug!("Found working UART COM{num}");
        }
    }

    interrupts::enable_interrupts();

    info!("Monnos is ready!");

    loop {}
}
