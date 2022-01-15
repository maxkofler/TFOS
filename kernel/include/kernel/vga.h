#ifndef __VGA_H__
#define __VGA_H__

#include <stdint.h>

#include "hardcodes/vga.h"

extern uint16_t VGA_WIDTH;
extern uint16_t VGA_HEIGHT;

//Default color is white on black
extern const uint8_t vga_cur_col;

//External font
extern unsigned char vga_8x8_font[];

static inline uint8_t vga_color(enum vga_color fg, enum vga_color bg){
	return fg | bg << 4;
}

static inline uint16_t vga_entry(uint8_t c, uint8_t color){
	return (uint16_t) c | (uint16_t) color << 8;
}

/**
 * @brief	Puts the specified character at the specified position using the color set
 * @param	pos			The offset to put the character to
 * @param	c			The character to put
 */
static inline void vga_put(uint16_t pos, uint8_t c){
	*(uint16_t*)(VGA_BASE_ADDRESS + (pos*2)) = vga_entry(c, vga_cur_col);
}

/**
 * @brief	Sets the specified register on the VGA chip
 * @param	reg 		The register to modify
 * @param	byte		The byte to put into the register
 */
void vga_set_reg(uint8_t reg, uint8_t byte);

/**
 * @brief	Initializes the VGA system to mode 0x11, 640x480 2 color
 */
void vga_setup();

/**
 * @brief	Puts the supplied character to a certain position in memory
 * @param	x			The x position to put the char to
 * @param	y			The y position to put the char to
 * @param	character	The character to put
 */
void vga_put_char_pos(uint8_t x, uint8_t y, uint8_t character);

/**
 * @brief	Puts the supplied character to the cursor position, newlines start a new line
 * @param	character	The character to put
 */
void vga_put_char(uint8_t character);

/**
 * @brief	Puts the supplied string onto the screen, newlines start a new line
 * @param	string		The string to put
 */
void vga_put_string(const char* string);

#endif