#include "vga.h"

namespace VGA{
    void VGA::clear(){
        uint16_t* buffer_end = this->_buffer + (this->_width * this->_height);

        for (uint16_t* pos = this->_buffer; pos < buffer_end; pos++){
            *pos = ' ' | this->_col << 8;
        }
    }
}