#ifndef __STRING_H__
#define __STRING_H__

#include <stdint.h>

/**
 * @brief	Converts an integer to a char* string
 * 
 * @param	num			The number to convert
 * @param	buffer		The buffer to use
 * @param	base		The base of the number
 * @return	char*		A pointer to the buffer provided
 */
char* itoa(int num, char* buffer, int base);

/**
 * @brief	Converts the character supplied to a number
 * @param	c			The character to convert
 */
uint8_t ctoi(char c);

#endif