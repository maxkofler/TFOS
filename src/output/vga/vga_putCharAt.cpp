#include "output/vga.h"

void VGA::putCharAt(size_t x, size_t y, unsigned char character){
    this->_screenStart[this->_width*y + x] = (uint16_t) character | (uint16_t) this->_curColor << 8;
}