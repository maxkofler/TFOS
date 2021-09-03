#ifndef __VGA_H__
#define __VGA_H__

#include <stdint.h>

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
								//
		void					init(uint16_t* vga_start, uint16_t width, uint16_t height);
		void					setColor(enum color fg, enum color bg);
		void					clear();

		void					put(uint16_t x, uint16_t y, char c);

		void					setCursor(uint16_t x, uint16_t y);
		void					updateCursor();

	private:
		uint8_t					_col;

		uint16_t				_width;
		uint16_t				_height;

		uint16_t				_c_x;
		uint16_t				_c_y;

		uint16_t*				_buffer;
	};
};



#endif