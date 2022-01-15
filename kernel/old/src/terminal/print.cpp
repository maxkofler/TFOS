#include "terminal.h"

namespace Terminal{
    void Terminal::print(char c){
		if (c == '\n'){
			uint16_t width = this->_vga->_width;
            this->_cursor_pos += (width - (this->_cursor_pos % width));
		} else {
			*((uint16_t*) this->_vga->_buffer + this->_cursor_pos) = (uint16_t) c | (uint16_t) this->_vga->_col << 8;
            this->_cursor_pos++;
		}

        this->_vga->_cursor_offset = this->_cursor_pos;
        this->_vga->updateCursor();
    }

    void Terminal::print(const char *msg){
        uint16_t index = 0;
        while (msg[index] != 0){
            switch(msg[index]){

                //Handle newline caracter by setting the cursor to the next line
                case '\n':{
                    uint16_t width = this->_vga->_width;
                    this->_cursor_pos += (width - (this->_cursor_pos % width));
                    index++;
                    break;
                }

                //Print default caracters
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

    void Terminal::print(char *msg, uint32_t len){
        for (uint32_t i = 0; i < len; i++){
            switch(msg[i]){

                //Handle newline caracter by setting the cursor to the next line
                case '\n':{
                    uint16_t width = this->_vga->_width;
                    this->_cursor_pos += (width - (this->_cursor_pos % width));
                    break;
                }

                //Print default caracters
                default:{
                    *((uint16_t*) this->_vga->_buffer + this->_cursor_pos) = (uint16_t) msg[i] | (uint16_t) this->_vga->_col << 8;
                    this->_cursor_pos++;
                }
            }
        }
    }
}