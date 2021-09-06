#include "terminal.h"

namespace Terminal{
    void Terminal::setSize(uint16_t w, uint16_t h){
        this->_vga->_width = w;
        this->_vga->_height = h;
    }
}