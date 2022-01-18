#include "kernel/memory.h"

/**
 * @brief	Copies <count> bytes from <source> to <dest>
 * @param	source 
 * @param	dest 
 * @param	count 
 */
void memcpy(uint8_t* source, uint8_t* dest, uint32_t count){
	for (uint32_t i = 0; i < count; i++){
		*(dest+i) = *(source+i);
	}
}