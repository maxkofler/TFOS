use alloc::boxed::Box;

use crate::monnos::io::pci::configuration::PCIDeviceHeader;

pub mod e1000;

const REGISTERED_DRIVERS: [&dyn NetworkDriverFactory; 1] = [&e1000::E1000Factory::new()];

pub fn check_pci_driver(header: &PCIDeviceHeader) -> Option<Box<dyn NetworkDriver>> {
    for driver in REGISTERED_DRIVERS {
        if driver.supports_pci_device(header) == SupportLevel::Full {
            if let Ok(driver) = driver.init_pci(header.clone()) {
                return Some(driver);
            }
        }
    }

    None
}

pub trait NetworkDriverFactory {
    fn supports_pci_device(&self, header: &PCIDeviceHeader) -> SupportLevel;

    fn init_pci(&self, header: PCIDeviceHeader) -> Result<Box<dyn NetworkDriver>, InitError>;
}

pub trait NetworkDriver {}

pub enum InitError {}

#[derive(PartialEq, Eq)]
pub enum SupportLevel {
    Full,
    Unsupported,
}
