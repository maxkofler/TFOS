#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

/**
 * @brief	Copies <count> bytes from <source> to <dest>
 * @param	source 
 * @param	dest 
 * @param	count 
 */
void memcpy(uint8_t* source, uint8_t* dest, uint32_t count);

#endif