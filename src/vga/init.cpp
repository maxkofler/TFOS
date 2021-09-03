#include "vga.h"

namespace VGA{
    void VGA::init(uint16_t* vga_pointer, uint16_t w, uint16_t h){
        this->_buffer = vga_pointer;
        this->_width = w;
        this->_height = h;

        clear();
    }
}