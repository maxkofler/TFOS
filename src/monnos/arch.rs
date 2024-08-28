//! Structures and utilities specific to the
//! target architecture.
//!
//! This place collects everything that does not
//! belong to any subsystem but needs some place.
#[cfg(target_arch = "x86")]
mod x86;
#[cfg(target_arch = "x86")]
pub use x86::*;
