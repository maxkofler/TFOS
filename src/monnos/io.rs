pub mod port;
use port::PortIOError;

pub enum IOError {
    Port(PortIOError)
}

impl From<PortIOError> for IOError {
    fn from(value: PortIOError) -> Self {
        Self::Port(value)
    }
}

