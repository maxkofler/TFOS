#include "output/terminal.h"

void Terminal::clear(){
    this->_x = 0;
    this->_y = 0;

    for (uint16_t y = 0; y < this->_vga.getHeight(); y++){
        for (uint16_t x = 0; x < this->_vga.getWidth(); x++){
            this->_vga.putCharAt(x, y, ' ');
        }
    }
}