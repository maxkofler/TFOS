#include "kernel/kernel.h"
#include "kernel/vga.h"
#include "kernel/string.h"

#include <stdarg.h>

char buffer[16];

/**
 * @brief	Similar to printf, but runs in kernel space
 * @param	format			Like the format string of printf
 * @param	...				Arguments
 * @return	uint32_t		The amount of characters printed, excluding the nullterminator
 */
uint32_t printk(const char* format, ...){
	va_list args;

	va_start(args, format);

	uint32_t i;
	char c, d;
	for(i = 0; format[i]; i++){
		c = format[i];
		switch(c){
		case '%':{
			i++;
			d = format[i];
			if (d == 0)
				break;

			switch(d){
			case 's':
				vga_put_string(va_arg(args, const char*));					break;

			case 'i':
				vga_put_string(itoa(va_arg(args, int), buffer, 10));		break;

			default:
				vga_put_char('?');
			}

			break;
		}

		default:
			vga_put_char(c);
		}
	}

	va_end(args);

	return 0;
}