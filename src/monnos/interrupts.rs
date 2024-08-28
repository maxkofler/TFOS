#[cfg(target_arch = "x86")]
mod int_x86;
#[cfg(target_arch = "x86")]
pub mod arch {
    //! Platform specific code to handle interrupts
    pub use super::int_x86::*;
}

/// Enables and configures the interrupt subsystem
pub fn enable_interrupts() {
    #[cfg(target_arch = "x86")]
    arch::enable_interrupts_x86();
}

/// A hub to manage interrupts centrally
pub struct InterruptHub {}
