#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include <stdint.h>

/**
 * @brief	Initializes the system call interface for the specified interrupt
 * @param	interrupt			The interrupt the system call handler should get registered for 
 */
void syscall_init(uint8_t interrupt);

#endif