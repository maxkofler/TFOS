#include "vga.h"
#include "io.h"
#include "hardcodes/hardcode_vga.h"

namespace VGA{
    void VGA::setCursor(uint16_t x, uint16_t y){
        this->_c_x = x;
        this->_c_y = y;

        updateCursor();
    }

    void VGA::updateCursor(){
        uint16_t offset_cursor = (this->_c_y * this->_width) + this->_c_x;

        IO::out(HARDCODE_VGA_CTRL, HARDCODE_VGA_OFFSET_HIGH);
        IO::out(HARDCODE_VGA_DATA, offset_cursor >> 8);
        IO::out(HARDCODE_VGA_CTRL, HARDCODE_VGA_OFFSET_LOW);
        IO::out(HARDCODE_VGA_DATA, offset_cursor);
    }
}