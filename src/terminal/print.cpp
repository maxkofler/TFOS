#include "terminal.h"

namespace Terminal{
    void Terminal::print(char c){
        *((uint16_t*) this->_vga->_buffer + this->_cursor_pos) = (uint16_t) c | (uint16_t) this->_vga->_col << 8;
        this->_cursor_pos++;
        this->_vga->_cursor_offset = this->_cursor_pos;
        this->_vga->updateCursor();
    }

    void Terminal::print(const char *msg){
        uint16_t index = 0;
        while (msg[index] != 0){
            switch(msg[index]){
                default:{
                    *((uint16_t*) this->_vga->_buffer + this->_cursor_pos) = (uint16_t) msg[index] | (uint16_t) this->_vga->_col << 8;
                    this->_cursor_pos++;
                    index++;
                }
            }
            
        }
        this->_vga->_cursor_offset = this->_cursor_pos;
        this->_vga->updateCursor();
    }
}