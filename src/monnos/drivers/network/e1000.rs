use alloc::boxed::Box;
use log::info;

use crate::monnos::io::{
    mmio::{RORegister, RWRegister, RegisterRead},
    pci::configuration::PCIDeviceHeader,
};

use super::{NetworkDriver, NetworkDriverFactory, SupportLevel};

pub struct E1000Factory {}
impl E1000Factory {
    pub const fn new() -> Self {
        Self {}
    }
}

pub struct E1000 {
    device: PCIDeviceHeader,
    registers: E1000RegisterBlock,
}

impl NetworkDriverFactory for E1000Factory {
    fn supports_pci_device(
        &self,
        header: &crate::monnos::io::pci::configuration::PCIDeviceHeader,
    ) -> SupportLevel
    where
        Self: Sized,
    {
        if header.vendor_id == 0x8086 && header.device_id == 0x100E {
            SupportLevel::Full
        } else {
            SupportLevel::Unsupported
        }
    }

    fn init_pci(
        &self,
        header: PCIDeviceHeader,
    ) -> Result<Box<dyn NetworkDriver>, super::InitError> {
        Ok(Box::new(E1000::init(header)))
    }
}

impl NetworkDriver for E1000 {}

impl E1000 {
    pub fn init(device: PCIDeviceHeader) -> Self {
        let bar0 = device.bars[0] as *mut ();

        let registers = unsafe { E1000RegisterBlock::new(bar0) };

        let mac = registers.status.read();

        info!("MAC: {mac:x}");

        Self { device, registers }
    }
}

pub struct E1000RegisterBlock {
    pub control: RWRegister<u32>,
    pub status: RORegister<u32>,
}

impl E1000RegisterBlock {
    pub unsafe fn new(bar: *mut ()) -> Self {
        Self {
            control: RWRegister::new(bar),
            status: RORegister::new(bar.byte_add(8)),
        }
    }
}
