//! The logging implementation for MONNOS
use core::{cell::SyncUnsafeCell, fmt::Write};

use log::{Level, Metadata, Record};

use super::drivers::uart::BlockingUART;

/// The logger implementation for the MONNOS kernel
pub struct MONNOSLogger {
    uart: SyncUnsafeCell<BlockingUART>,
    level: Level,
}

impl MONNOSLogger {
    /// Creates a new logger from a blocking UART
    /// # Arguments
    /// * `uart` - The UART to use for logging
    /// * `level` - The level at which this logger should output
    pub fn new(uart: BlockingUART, level: Level) -> Self {
        Self {
            uart: SyncUnsafeCell::new(uart),
            level,
        }
    }
}

impl log::Log for MONNOSLogger {
    fn enabled(&self, metadata: &Metadata) -> bool {
        metadata.level() <= self.level
    }

    fn log(&self, record: &Record) {
        if self.enabled(record.metadata()) {
            let uart = unsafe { self.uart.get().as_mut().unwrap() };

            writeln!(uart, "{} - {}", record.level(), record.args())
                .expect("Output the log message");
        }
    }

    fn flush(&self) {}
}
