#include "output/vga.h"

void VGA::setColor(uint8_t fg, uint8_t bg){
    this->_curColor = fg | bg << 4;
}