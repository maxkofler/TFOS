#ifndef __VGA_H__
#define __VGA_H__

namespace VGA{
	class VGA;
}

#include <stdint.h>

#include "terminal.h"

namespace VGA{
		enum color{
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		BROWN = 6,
		LIGHT_GREY = 7,
		DARK_GREY = 8,
		LIGHT_BLUE = 9,
		LIGHT_GREEN = 10,
		LIGHT_CYAN = 11,
		LIGHT_RED = 12,
		LIGHT_MAGENTA = 13,
		LIGHT_BROWN = 14,
		WHITE = 15,
	};

	class VGA{

	public:
		VGA(uint16_t* vga_start, uint16_t width, uint16_t height);

		/**
		 * @brief	Sets the VGA color of the following characters
		 * @param	fg			Foreground
		 * @param	bg			Background
		 */
		void					setColor(enum color fg, enum color bg);

		/**
		 * @brief	Clears the screen
		 * @note	The background of the whole screen will be the background color
		 */
		void					clear();

		/**
		 * @brief	Puts the provided character c on the screen
		 * @param	x			X coordinate
		 * @param	y			Y coordinate
		 * @param	c			The character to pring
		 */
		void					put(uint16_t x, uint16_t y, char c);

		/**
		 * @brief	Moves the text mode cursor of the vga card to the specified location
		 * @param	x			X coordinate
		 * @param	y			Y coordinate
		 * @note	Calls updateCursor() immediately
		 */
		void					setCursor(uint16_t x, uint16_t y);

		/**
		 * @brief	Moves the cursor to the coordinates specified by setCursor()
		 * @note	Gets called by setCursor() automatically
		 */
		void					updateCursor();

		/**
		 * @brief	Enabled the text mode cursor of the vga card
		 * @param	cStart		Specifies the first horizontal line from to down to draw, read note
		 * @param	cEnd		Specifies the last horizontal line from to down to draw, read not
		 * @note	enableCursor(0, 15)		->	full height
		 *			enableCursor(14, 15)	->	small underscore cursor: '_'
		 */
		void					enableCursor(uint8_t cStart = 0, uint8_t cEnd = 15);

		friend class 			Terminal::Terminal;

	private:
		uint8_t					_col;

		uint16_t				_width;
		uint16_t				_height;

		uint16_t				_cursor_offset;

		uint16_t*				_buffer;
	};
};



#endif
