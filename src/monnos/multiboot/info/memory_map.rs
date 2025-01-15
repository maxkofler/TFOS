//! Tools for parsing and working with memory
//! map descriptions in the multiboot standard.
use core::fmt::Debug;

/// The structure to describe a memory map
/// in the multiboot information header
#[derive(Debug)]
pub struct MemoryMap {
    /// The data that is contained in this memory map
    data: &'static [u8],
}

impl MemoryMap {
    /// Creates a new memory map that wraps the supplied
    /// buffer containing memory information
    pub fn new(data: &'static [u8]) -> Self {
        Self { data }
    }

    /// Creates an iterator over the memory map
    /// that yields memory segments
    pub fn iter(self) -> MemoryMapIterator {
        MemoryMapIterator { data: self.data }
    }
}

/// An iterator over memory regions in the multiboot memory
/// map structure
pub struct MemoryMapIterator {
    data: &'static [u8],
}

impl Iterator for MemoryMapIterator {
    type Item = Option<MemoryRegion>;

    fn next(&mut self) -> Option<Self::Item> {
        if !self.data.is_empty() {
            let size = u32::from_le_bytes(self.data[0..4].try_into().unwrap());
            self.data = &self.data[4..];

            let ptr = self.data.as_ptr();

            let region_raw: &MemoryRegionRaw = unsafe { &*(ptr as *const MemoryRegionRaw) };
            let region = MemoryRegion::try_from_raw(region_raw.clone());

            self.data = &self.data[size as usize..];

            Some(region)
        } else {
            None
        }
    }
}

/// A memory region as described by the multiboot
/// information structure
pub struct MemoryRegion {
    /// A slice over the data that is available
    /// in this memory region
    pub data: &'static mut [u8],
    /// The type of memory region
    pub ty: MemoryRegionType,
}

impl MemoryRegion {
    fn try_from_raw(mut value: MemoryRegionRaw) -> Option<Self> {
        if value.base == 0 {
            value.base += 1;
            value.length -= 1;
        }

        let ty = MemoryRegionType::from_u32(value.ty)?;

        Some(Self {
            data: unsafe {
                core::slice::from_raw_parts_mut(value.base as *mut u8, value.length as usize)
            },
            ty,
        })
    }
}

impl Debug for MemoryRegion {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        f.debug_struct("MemoryRegion")
            .field("start", &self.data.as_ptr())
            .field("size", &self.data.len())
            .field("type", &self.ty)
            .finish()
    }
}

/// The type of memory region at hand
#[repr(u8)]
#[derive(Debug)]
pub enum MemoryRegionType {
    /// Normally usable RAM
    RAM = 0,
    /// Memory that holds ACPI information
    ACPI = 3,
    /// Memory regions that should be preserved
    Preserve = 4,
    /// Unusable memory regions that are defective
    /// or unusable otherwise
    Unusable = 5,
}

impl MemoryRegionType {
    /// Infers the memory region type from the
    pub fn from_u32(data: u32) -> Option<Self> {
        match data {
            0 => Some(Self::RAM),
            3 => Some(Self::ACPI),
            4 => Some(Self::Preserve),
            5 => Some(Self::Unusable),
            _ => None,
        }
    }
}

/// The raw representation of a memory region as specified in
/// the multiboot header structure
#[repr(C, align(1))]
#[derive(Debug, Clone)]
pub struct MemoryRegionRaw {
    /// The base of the memory region
    pub base: u64,
    /// The length of the memory region in bytes
    pub length: u32,
    /// The type of the memory region:
    /// * `0` - Normal RAM
    /// * `3` - ACPI tables
    /// * `4` - Memory that needs to be preserved
    /// * `5` - Unusable memory (defect or reserved)
    pub ty: u32,
}
