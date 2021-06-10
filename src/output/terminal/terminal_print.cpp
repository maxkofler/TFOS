#include "output/terminal.h"

#include "libc/string.h"

void Terminal::print(const char* string){
    for (size_t i = 0; i < strlen(string); i++){
        this->_vga.putCharAt(this->_x, this->_y, string[i]);
        this->_x++;
    }
}