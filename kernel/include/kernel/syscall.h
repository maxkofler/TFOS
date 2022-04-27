#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include "registers.h"

#include <stdint.h>

#define MAX_SYSCALLS 64
typedef uint8_t syscall_id;

#define LOG_PREFIX_SCALL "[SCALL] "

/**
 * @brief	Initializes the system call interface for the specified interrupt
 * @param	interrupt			The interrupt the system call handler should get registered for 
 */
void syscall_init(uint8_t interrupt);

/**
 * @brief	Registers a new system call with the specified id
 * @param	id					The id of the systemcall, the parameter stored in eax to set the call
 * @param	handler				The handler function that gets called when the syscall is called
 */
void syscall_register(syscall_id id, void (*handler)(registers_t*));

#endif