//! Tools for working with modules in the
//! multiboot standard

use crate::monnos::util::str_from_nullterminated;

/// A module that can be loaded with the kernel
/// by the bootloader as specified in the multiboot specification
#[derive(Debug)]
pub struct Module<'a> {
    /// The module's binary data
    pub data: &'a [u8],
    /// The string passed to the module
    pub string: &'a str,
}

/// The raw module data as it lives in memory,
/// can be parsed into a [Module] using `.parse()`
#[repr(C, align(4))]
#[derive(Debug)]
pub struct ModuleRaw {
    /// The start of the module's binary data
    pub mod_start: u32,
    /// The end of the module's binary data
    pub mod_end: u32,
    /// A pointer to the nullterminated string passed for this module
    pub string: u32,
    reserved: u32,
}

impl ModuleRaw {
    /// Parses a raw module into a parsed [Module]
    pub fn parse<'a>(&'a self) -> Module<'a> {
        Module::from(self)
    }
}

impl<'a> From<&ModuleRaw> for Module<'a> {
    fn from(value: &ModuleRaw) -> Self {
        let data_len = value.mod_end - value.mod_start;
        let data = value.mod_start as *const u8;

        Self {
            data: unsafe { core::slice::from_raw_parts(data, data_len as usize) },
            string: unsafe { str_from_nullterminated(value.string as *const u8) },
        }
    }
}
