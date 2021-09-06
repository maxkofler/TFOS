#include "vga.h"

namespace VGA{
    void VGA::clear(){
        uint16_t buffer_len = this->_width * this->_height;

        for (uint16_t pos = 0; pos < buffer_len - 1; pos++){
            *((uint16_t*)(this->_buffer + pos)) = ' ' | this->_col << 8;
        }

        this->_cursor_offset = 0;
        updateCursor();
    }
}