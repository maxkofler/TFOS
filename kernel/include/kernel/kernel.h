#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <stdint.h>

/**
 * @brief	Similar to printf, but runs in kernel space
 * @param	format			Like the format string of printf
 * @param	...				Arguments
 * @return	uint32_t		The amount of characters printed, excluding the nullterminator
 * @note	Supported formats:
 * 							%s	Prints an argument as string
 * 							%i	Prints an argument as integer
 */
uint32_t printk(const char* format, ...);

#endif