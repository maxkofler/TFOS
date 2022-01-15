#ifndef __STRING_H__
#define __STRING_H__

#include <stdint.h>

/**
 * @brief	Converts the supplied integer to a string
 * @param	num 
 * @return	const char* 
 */
const char* itoa(int num);

uint32_t strlen(const char* string);

#endif