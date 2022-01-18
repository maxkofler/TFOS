#include "kernel/vga.h"
#include "kernel/io.h"
#include "kernel/memory.h"

uint16_t VGA_WIDTH = 80;
uint16_t VGA_HEIGHT = 25;

const uint8_t vga_cur_col = 0x0F;

static uint16_t vga_cur_pos = 0;
static uint8_t vga_cursor_x = 0;
static uint8_t vga_cursor_y = 0;

/**
 * @brief	Sets the specified register on the VGA chip
 * @param	reg 		The register to modify
 * @param	byte		The byte to put into the register
 */
void vga_set_reg(uint8_t reg, uint8_t byte){
	outb(VGA_REGISTER_CTRL, reg);
	outb(VGA_REGISTER_DATA, byte);
}

/**
 * @brief	Initializes the VGA system to mode 0x11, 640x480 2 color
 */
void vga_setup(){
	VGA_WIDTH = 80;
	VGA_HEIGHT = 60;
	vga_set_reg(0x06, 0b00000001);
	vga_cur_pos = 0;
}

void vga_new_line(void){
	vga_put_char_pos(vga_cursor_x, vga_cursor_y, ' ');
	vga_cursor_y++;
	vga_cursor_x = 0;

	while (vga_cursor_y >= VGA_HEIGHT){
		memcpy(
			(uint8_t*)(VGA_BASE_ADDRESS + (VGA_WIDTH*8)),
			(uint8_t*)(VGA_BASE_ADDRESS),
			VGA_WIDTH * ((VGA_HEIGHT-1)*8)
		);
		vga_cursor_y--;
	}

	for(uint16_t i = 0; i < VGA_WIDTH; i++)
		vga_put_char_pos(i, VGA_HEIGHT-1, ' ');
}

/**
 * @brief	Puts the supplied character to a certain position in memory
 * @param	x			The x position to put the char to
 * @param	y			The y position to put the char to
 * @param	character	The character to put
 */
void vga_put_char_pos(uint8_t x, uint8_t y, uint8_t character){
	uint16_t c = character*8;
	uint16_t offset = ((y * 8 * VGA_WIDTH) + x);
	for(uint16_t i = 0; i <  8; i++){
		*(uint8_t*)(0xa0000 + offset + (i*80)) = vga_8x8_font[c+i];
	}
}

void vga_put_char(uint8_t character){
	if (character == '\n'){
		vga_new_line();
		return;
	}

	vga_put_char_pos(vga_cursor_x, vga_cursor_y, character);

	vga_cursor_x++;

	if (vga_cursor_x >= VGA_WIDTH){
		vga_cursor_y++;
		vga_cursor_x = 0;
	}

	vga_put_char_pos(vga_cursor_x, vga_cursor_y, '_');
}

/**
 * @brief	Puts the supplied string onto the screen, newlines start a new line
 * @param	string		The string to put
 */
void vga_put_string(const char* string){
	uint16_t string_pos = 0;
	for(; string[string_pos]; string_pos++){
		if (string[string_pos] == '\n'){
			vga_new_line();
			continue;
		}

		vga_put_char_pos(vga_cursor_x, vga_cursor_y, string[string_pos]);
		vga_cursor_x++;

		if (vga_cursor_x >= VGA_WIDTH){
			vga_cursor_y++;
			vga_cursor_x = 0;
		}
	}
	vga_put_char_pos(vga_cursor_x, vga_cursor_y, '_');
}