#include "vga.h"

namespace VGA{
    VGA::VGA(uint16_t* buffer, uint16_t w, uint16_t h){
        this->_buffer = buffer;
        this->_width = w;
        this->_height = h;
    }
}