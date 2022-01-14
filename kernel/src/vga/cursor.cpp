#include "vga.h"
#include "io.h"
#include "hardcodes/hardcode_vga.h"

namespace VGA{
    void VGA::setCursor(uint16_t x, uint16_t y){
        this->_cursor_offset = (y * this->_width) + x;
        updateCursor();
    }

    void VGA::updateCursor(){
        IO::outb(HARDCODE_VGA_CTRL, HARDCODE_VGA_OFFSET_HIGH);
        IO::outb(HARDCODE_VGA_DATA, (uint8_t)(this->_cursor_offset >> 8));
        IO::outb(HARDCODE_VGA_CTRL, HARDCODE_VGA_OFFSET_LOW);
        IO::outb(HARDCODE_VGA_DATA, (uint8_t)(this->_cursor_offset & 0xFF));
    }

    void VGA::enableCursor(uint8_t cStart, uint8_t cEnd){
        IO::outb(0x3D4, 0x0A);
        IO::outb(0x3D5, (IO::inb(0x3D5) & 0xC0) | cStart);
    
        IO::outb(0x3D4, 0x0B);
        IO::outb(0x3D5, (IO::inb(0x3D5) & 0xE0) | cEnd);
    }
}