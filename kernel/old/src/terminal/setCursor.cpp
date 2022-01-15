#include "terminal.h"

void Terminal::Terminal::setCursor(uint16_t x, uint16_t y){
	this->_cursor_pos = (this->_vga->_width * y) + x;
}