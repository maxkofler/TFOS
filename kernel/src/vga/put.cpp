#include "vga.h"

namespace VGA{
    void VGA::put(uint16_t x, uint16_t y, char c){
        *((uint16_t*)(this->_buffer + (y*this->_width) + x)) = (uint16_t) c | (uint16_t) this->_col << 8;
    }
}