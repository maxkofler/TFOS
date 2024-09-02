//! Tools for working with the multiboot information structure

use log::debug;
use memory_map::MemoryMap;
use module::ModuleRaw;

pub mod memory_map;
pub mod module;

use crate::monnos::util::str_from_nullterminated;

/// The raw multiboot information structure as it lives in memory
/// and as it can be parsed from memory
#[repr(C, align(4))]
#[derive(Debug)]
struct MultibootInformationRaw {
    flags: u32,

    mem_lower: u32,
    mem_upper: u32,

    boot_device: u32,

    cmdline: u32,

    mods_count: u32,
    mods_addr: u32,

    syms: [u32; 4],

    mmap_length: u32,
    mmap_addr: u32,
}

/// The multiboot information structure provided by
/// the bootloader as information to the kernel
#[derive(Debug, Default)]
pub struct MultibootInformation<'a> {
    // Present if flags[0] is set
    /// The amount of lower memory (starting from addr 0) in kilobytes
    pub mem_lower: Option<u32>,
    /// The amount of upper memory (starting from addr 1M) in kilobytes
    pub mem_upper: Option<u32>,

    // Present if flags[1] is set
    /// Information about the device that was booted from
    pub boot_device: Option<u32>,

    // Present if flags[2] is set
    /// The kernel command line
    pub cmdline: Option<&'a str>,

    // Present if flags[3] is set
    /// Modules that are passed to the kernel
    pub modules: Option<&'a [ModuleRaw]>,

    // Present if flags[6] is set
    /// Provides
    pub memory_map: Option<MemoryMap<'a>>,
}

/// Parses the boot information that the multiboot
/// bootloader provides for us to use and work with
/// # Arguments
/// * `position` - The pointer data to where the multiboot information lives in memory
pub fn parse_boot_info(position: u32) -> MultibootInformation<'static> {
    let ptr = position as *const MultibootInformationRaw;

    let info_raw = unsafe { &*ptr };
    let flags = info_raw.flags;

    debug!("{:#x?}", info_raw);

    let mut info = MultibootInformation::default();

    if flags & 1 == 1 {
        info.mem_lower = Some(info_raw.mem_lower);
        info.mem_upper = Some(info_raw.mem_upper);
    }

    if (flags >> 1) & 1 == 1 {
        info.boot_device = Some(info_raw.boot_device);
    }

    if (flags >> 2) & 1 == 1 {
        info.cmdline = Some(unsafe { str_from_nullterminated(info_raw.cmdline as *const u8) });
    }

    if (flags >> 3) & 1 == 1 {
        let mods_raw = unsafe {
            core::slice::from_raw_parts(
                info_raw.mods_addr as *const ModuleRaw,
                info_raw.mods_count as usize,
            )
        };

        info.modules = Some(mods_raw);
    }

    if (flags >> 6) & 1 == 1 {
        let mmap_raw = unsafe {
            core::slice::from_raw_parts(
                info_raw.mmap_addr as *const u8,
                info_raw.mmap_length as usize,
            )
        };

        info.memory_map = Some(MemoryMap::new(mmap_raw))
    }

    info
}
