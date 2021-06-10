#include "output/vga.h"

VGA::VGA(){
    this->_curColor = 0;
    this->_width = 0;
    this->_height = 0;
}

VGA::VGA(size_t width, size_t height, uint16_t* screenStart){
    this->_curColor = 0;
    this->_width = width;
    this->_height = height;
    this->_screenStart = screenStart;
}

/*

inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
        return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
        return (uint16_t) uc | (uint16_t) color << 8;
}

*/