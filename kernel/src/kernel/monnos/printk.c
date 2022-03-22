#include "kernel/monnos.h"
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

	uint32_t i = 0;
	uint8_t level = K_LEVEL_MAX;

	if (format[i] == *K_LEVEL_HEADER){
		i++;
		level = ctoi(format[i]);
		i++;

		//Only select out loglevels that can not be determined
		if (level > loglevel_current)
			return 0;
	}

	if (level < K_LEVEL_MAX){
		vga_put_string("[ ");
		vga_put_string(loglevel_to_str(level));
		vga_put_string(" ] ");
	}

	char c, d;
	for(; format[i]; i++){
		c = format[i];
		switch(c){
		case '%':{
			i++;
			d = format[i];
			if (d == 0)
				break;

			switch(d){
			case 'c':
				vga_put_char(va_arg(args, int));							break;

			case 's':
				vga_put_string(va_arg(args, const char*));					break;

			case 'i':
				vga_put_string(itoa(va_arg(args, int), buffer, 10));		break;

			case 'x':
				vga_put_string(itoa(va_arg(args, int), buffer, 16));		break;

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
