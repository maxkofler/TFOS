//! PCI configuration space

use core::mem::size_of;

use super::{config_io_read_register, config_io_read_registers};

mod deviceheader;
pub use deviceheader::PCIDeviceHeader;

/// A header in the PCI configuration space
#[derive(Debug)]
pub enum PCIHeader {
    /// A device
    Device(PCIDeviceHeader),
    /// Something unknown
    Unknown,
}

impl PCIHeader {
    /// Tries to retrieve a PCI header from the specified bus, device and function
    /// # Arguments
    /// * `bus` - The PCI bus to get the header from
    /// * `device` - The PCI device to get the header from
    /// * `function` - The PCI function to get the header from
    /// # Returns
    /// The header if a device is present
    pub fn try_get(bus: u8, device: u8, function: u8) -> Option<Self> {
        let device_vendor_id = config_io_read_register(bus, device, function, 0);
        if (device_vendor_id & 0xFFFF) == 0xFFFF {
            return None;
        }

        let header_type = config_io_read_register(bus, device, function, 12);
        let header_type = (header_type >> 16) & 0xFF;

        match header_type {
            0x00 => {
                let data: [u32; size_of::<PCIDeviceHeader>() / 4] =
                    config_io_read_registers(bus, device, function);

                let device_header: PCIDeviceHeader = unsafe { core::mem::transmute(data) };

                Some(PCIHeader::Device(device_header))
            }
            _ => Some(PCIHeader::Unknown),
        }
    }
}
