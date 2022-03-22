#include "kernel/memory.h"

#ifdef DEBUG
#include "kernel/monnos.h"
#endif

#ifdef DEBUG_PRINT_INIT
	#ifndef DEBUG
		#error You have to define DEBUG to use DEBUG_PRINT_INIT
	#endif
#endif

#ifdef DEBUG_PRINT_ALLOCS
	#ifndef DEBUG
		#error You have to define DEBUG to use DEBUG_PRINT_ALLOCS
	#endif
#endif

static void* dynamic_mem_start;
static void* dynamic_mem_next_byte;

/**
 * @brief	Initializes the dynamic memory allocation subsystem
 * @param	start			The starting adress
 */
void mem_init_dynamic_memory(uint32_t start){
	dynamic_mem_start = (void*)start;
	dynamic_mem_next_byte = dynamic_mem_start;

	#ifdef DEBUG_PRINT_INIT
	printk("Starting dynamic memory allocations from 0x%x\n", dynamic_mem_start);
	#endif
}

/**
 * @brief	Reserves the specified amount of bytes
 * @param	size			The amount of bytes to reserve
 * @return	A pointer to the allocated memory
 */
void* kmalloc(uint32_t size){
	void* ret = dynamic_mem_next_byte;

	dynamic_mem_next_byte += size;

	#ifdef DEBUG_PRINT_ALLOCS
	printk("Reserved %i bytes at 0x%x\n", size, (uint32_t)ret);
	#endif

	return ret;
}

/**
 * @brief	Copies <count> bytes from <source> to <dest>
 * @param	source			A pointer to the source of the copy
 * @param	dest			A pointer to the destination
 * @param	count			The amount of bytes to copy
 */
void memcpy(uint8_t* source, uint8_t* dest, uint32_t count){
	for (uint32_t i = 0; i < count; i++){
		*(dest+i) = *(source+i);
	}
}
