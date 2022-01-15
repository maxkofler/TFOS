#include "vga.h"

namespace VGA{
    void VGA::setColor(enum color fg, enum color bg){
        this->_col = fg | bg << 4;
    }
}