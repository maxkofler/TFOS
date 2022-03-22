#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

//////////
//	Debugging options (uncomment to enable)
/*
#define DEBUG
#define DEBUG_PRINT_INIT
#define DEBUG_PRINT_ALLOCS
*/
//
//////////

/**
 * @brief	Initializes the dynamic memory allocation subsystem
 * @param	start			The starting adress
 */
void mem_init_dynamic_memory(uint32_t start);

/**
 * @brief	Reserves the specified amount of bytes
 * @param	size			The amount of bytes to reserve
 * @return	A pointer to the allocated memory
 */
void* kmalloc(uint32_t size);

/**
 * @brief	Copies <count> bytes from <source> to <dest>
 * @param	source			A pointer to the source of the copy
 * @param	dest			A pointer to the destination
 * @param	count			The amount of bytes to copy
 */
void memcpy(uint8_t* source, uint8_t* dest, uint32_t count);

#endif