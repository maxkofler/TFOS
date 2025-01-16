//! Memory-mapped IO functionality

/// The core trait each memory-mapped register has
/// to implement
pub trait MMIORegister<T> {
    /// Returns the pointer to the register's base
    fn ptr(&self) -> *mut T;
}

/// Functions to read from a memory-mapped register
pub trait RegisterRead<T>: MMIORegister<T> {
    /// Reads data from the register in a volatile manner
    fn read(&self) -> T {
        unsafe { self.ptr().read_volatile() }
    }
}

/// Functions to write to a memory-mapped register
pub trait RegisterWrite<T>: MMIORegister<T> {
    /// Writes to the register in a volatile manner
    /// # Arguments
    /// * `data` - The data to write
    fn write(&self, data: T) {
        unsafe { self.ptr().write_volatile(data) }
    }
}

/// Implements a read-write memory-mapped register
pub struct RWRegister<T> {
    ptr: *mut T,
}

impl<T> RWRegister<T> {
    /// Creates a new read-write memory-mapped register
    /// # Arguments
    /// * `ptr` - The pointer to the register
    /// # Safety
    /// This function is unsafe as it creates a `safe`
    /// handle for a unchecked pointer
    pub unsafe fn new(ptr: *mut ()) -> Self {
        Self { ptr: ptr as *mut T }
    }
}

impl<T> MMIORegister<T> for RWRegister<T> {
    fn ptr(&self) -> *mut T {
        self.ptr
    }
}

impl<T> RegisterRead<T> for RWRegister<T> {}
impl<T> RegisterWrite<T> for RWRegister<T> {}

/// A read-only memory-mapped register
pub struct RORegister<T> {
    ptr: *mut T,
}

impl<T> RORegister<T> {
    /// Creates a new read-only memory-mapped register
    /// # Arguments
    /// * `ptr` - The pointer to the register
    /// # Safety
    /// This function is unsafe as it creates a `safe`
    /// handle for a unchecked pointer
    pub unsafe fn new(ptr: *mut ()) -> Self {
        Self { ptr: ptr as *mut T }
    }
}

impl<T> MMIORegister<T> for RORegister<T> {
    fn ptr(&self) -> *mut T {
        self.ptr
    }
}

impl<T> RegisterRead<T> for RORegister<T> {}
