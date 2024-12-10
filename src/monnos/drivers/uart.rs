//! The UART driver

use core::fmt::Write;

use crate::monnos::io::port::{in8, out8, out8_bit};

/// The 8 default base ports for COM1-8 on a standard IBM PC
pub const COM_BASE: [u16; 8] = [0x3f8, 0x2f8, 0x3e8, 0x2e8, 0x5f7, 0x4f8, 0x5e8, 0x4e8];

/// A blocking UART port
pub struct BlockingUART {
    base: u16,
}

impl BlockingUART {
    /// Creates a new UART and checks if it is accessible
    /// by doing a loopback test
    /// # Arguments
    /// * `base` - The base IO port
    pub fn new(base: u16) -> Option<Self> {
        // Do a self test before giving back the UART
        let mut _self = Self { base };

        _self.set_loopback(true);
        unsafe { _self.write_unchecked(0xA5) };
        let res = unsafe { _self.read_unchecked() };
        _self.set_loopback(false);

        if res != 0xA5 {
            None
        } else {
            Some(_self)
        }
    }

    /// Sets the state of the loopback flag in the MCR (Modem Control Register)
    /// # Arguments
    /// * `enabled` - Whether to enable the loopback mode
    pub fn set_loopback(&mut self, enabled: bool) {
        // Register 4 (Modem Control Register)
        // Bit 4 (Loopback mode)
        out8_bit(self.base + 4, 4, enabled)
    }

    /// Returns if the UART is ready for more bytes.
    ///
    /// Note that the UART may still have bytes in its FIFO ready to be sent.
    /// This function is just for checking if a new byte can be pushed onto the FIFO.
    pub fn ready_for_data(&self) -> bool {
        // Register 5 (Line Status Register)
        // Bit 5 (Empty Transmitter Holding Register)
        in8(self.base + 5) >> 5 & 0x01 == 0x01
    }

    /// Returns if the UART has some data to read
    pub fn data_available(&self) -> bool {
        // Register 5 (Line Status Register)
        // Bit 0 (Data Ready)
        in8(self.base + 5) & 0x01 == 0x01
    }

    /// Writes a byte in blocking manner
    ///
    /// This function blocks the thread until the UART can pick up the byte
    /// # Arguments
    /// * `byte` - The byte to send
    pub fn write_byte_blocking(&mut self, byte: u8) {
        while !self.ready_for_data() {}

        unsafe { self.write_unchecked(byte) }
    }

    /// Reads a byte in blocking manner
    ///
    /// This function blocks the thread until the UART received a byte
    pub fn read_byte_blocking(&mut self) -> u8 {
        while !self.data_available() {}

        unsafe { self.read_unchecked() }
    }
}

// Implementation block for unsafe functions
impl BlockingUART {
    /// Creates a new blocking UART without any checks
    /// # Arguments
    /// * `base` - The base port for the UART chip
    /// # Safety
    /// This function does not check for anything
    pub unsafe fn new_unchecked(base: u16) -> Self {
        Self { base }
    }

    /// Reads from the receiver buffer directly without checking
    /// if there is data available
    /// # Safety
    /// This will not check if there is valid data to be read
    pub unsafe fn read_unchecked(&mut self) -> u8 {
        in8(self.base)
    }

    /// Writes directly to the Transmit Holding Register without
    /// checking if the UART can accept new bytes
    /// # Safety
    /// This will not check if the buffer is writable or ready
    pub unsafe fn write_unchecked(&mut self, byte: u8) {
        out8(self.base, byte)
    }
}

impl Write for BlockingUART {
    fn write_str(&mut self, s: &str) -> core::fmt::Result {
        for c in s.bytes() {
            self.write_byte_blocking(c)
        }

        Ok(())
    }
}
