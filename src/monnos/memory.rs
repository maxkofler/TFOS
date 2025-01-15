use core::alloc::GlobalAlloc;

use log::debug;

#[global_allocator]
static GLOBAL: MONNOSAllocator = MONNOSAllocator;

static mut MEMORY_AREA: Option<MemoryArea> = None;

pub unsafe fn set_memory_area(area: MemoryArea) {
    MEMORY_AREA = Some(area)
}

struct MONNOSAllocator;

unsafe impl GlobalAlloc for MONNOSAllocator {
    unsafe fn alloc(&self, layout: core::alloc::Layout) -> *mut u8 {
        // This is technically bad, but since we're single-threaded for now,
        // this should be fine until we start encountering interrupts with allocations
        #[allow(static_mut_refs)]
        let area = MEMORY_AREA.as_mut().expect("Expected a memory area");

        let ptr = area.allocate(layout.size());

        debug!(
            "Allocating {} bytes, {} remaining",
            layout.size(),
            area.remaining()
        );

        ptr.expect("OOM") as *mut u8
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: core::alloc::Layout) {
        debug!("Deallocated {} ({} bytes)", ptr as usize, layout.size());
    }
}

pub struct MemoryArea {
    pub position: usize,
    pub size: usize,
    data: *mut (),
}

impl MemoryArea {
    pub fn new(data: *mut (), size: usize) -> Self {
        Self {
            position: 0,
            size,
            data,
        }
    }

    pub fn allocate(&mut self, size: usize) -> Option<*mut ()> {
        if (self.position + size) > self.size {
            return None;
        }

        let ptr = unsafe { self.data.byte_add(self.position + size) };

        self.position += size;

        Some(ptr)
    }

    pub fn remaining(&self) -> usize {
        self.size - self.position
    }
}
