#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <stdint.h>

namespace Terminal{
    class Terminal;
}

#include "vga.h"

namespace Terminal{
    class Terminal{
    public:

		/**
		 * @brief	Provides this module with a vga object to draw on
		 * @param	vga			The vga module
		 */
		void					setVGA(VGA::VGA *vga);

		/**
		 * @brief	Sets the terminal size in characters
		 * @param	w			Width
		 * @param	h			Height
		 */
		void					setSize(uint16_t w, uint16_t h);

		/**
		 * @brief	Puts the character c to the cursor position, progresses the cursor
		 * @param	c			The character to put
		 * @note	Wraps the cursor to the next line at line end or if a newline is submitted
		 */
		void					print(char c);

		/**
		 * @brief	Prints a string from the current cursor position on
		 * @details Wraps the cursor around
		 * @param	msg			The string to print
		 * @note	Wraps the cursor to the next line at line end or if a newline is submitted
		 */
		void					print(const char *msg);

		/**
		 * @brief	Prints a string from the current cursor position on
		 * @details	Wraps the cursor around
		 * @param	msg			The string to print
		 * @param	len			The amount of characters to print
		 * @note	Wraps the cursor to the next line at line end or if a newline is submitted
		 */
		void					print(char *msg, uint32_t len);

		/**
		 * @brief	Repositiones the text mode cursor of the vga module if enabled
		 * @param	x			X position in characters
		 * @param	y			Y position in characters
		 */
		void					setCursor(uint16_t x, uint16_t y);


    private:
		VGA::VGA*               _vga;

		uint16_t				_cursor_pos = 0;
    };
}

#endif
