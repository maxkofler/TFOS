//! String lookups for the various PCI-related codings

/// Returns a human readable string that gives some information about a PCI device
/// # Arguments
/// * `class` - The PCI class to look for
/// * `subclass` - The PCI subclass to look for
/// * `programming_interface` - The PCI programming interface to look for
pub fn get_pci_class_string(class: u8, subclass: u8, programming_interface: u8) -> &'static str {
    match class {
        0x00 => match subclass {
            _ => "Unclassified PCI Device",
        },
        0x01 => match subclass {
            0x00 => "SCSI Mass Storage Controller",
            0x01 => "IDE Controller",
            0x02 => "Floppy disk controller",
            0x03 => "IPI bus controller",
            0x04 => "RAID controller",
            0x05 => "ATA controller",
            0x06 => match programming_interface {
                0x00 => "SATA controller - vendor specific",
                0x01 => "SATA controller - AHCI",
                0x02 => "Serial Storage Bus Interface",
                _ => "Unknown SATA controller",
            },
            _ => "Unknown Mass Storage Controller",
        },
        0x02 => match subclass {
            0x00 => "Ethernet Controller",
            _ => "Unknown Network Controller",
        },
        0x03 => match subclass {
            _ => "Unknown Display Controller",
        },
        0x04 => match subclass {
            _ => "Unknown Multimedia Controller",
        },
        0x05 => match subclass {
            _ => "Unknown Memory Controller",
        },
        0x06 => match subclass {
            0x0 => "Host Bridge",
            0x1 => "ISA Bridge",
            0x2 => "EISA Bridge",
            0x3 => "MCA Bridge",
            0x4 => match programming_interface {
                0x0 => "PCI to PCI Bridge (Normal Decode)",
                0x1 => "PCI to PCI Bridge (Subtractive Decode)",
                _ => "Unknown PCI to PCI Bridge",
            },
            _ => "Unknown Bridge",
        },
        0x07 => match subclass {
            _ => "Unknown Simple Communications Controller",
        },
        0x08 => match subclass {
            _ => "Unknown Base System Peripheral",
        },
        0x09 => match subclass {
            _ => "Unknown Input Device Controller",
        },
        _ => "Unknown PCI Device",
    }
}
