#include "kernel/syscall.h"
#include "kernel/monnos.h"
#define LOG_PREFIX LOG_PREFIX_SCALL

//The array to the syscall handlers
extern void (*syscall_handlers[MAX_SYSCALLS])(registers_t*);


void syscall_register(syscall_id id, void (*handler)(registers_t*)){

	if (id >= MAX_SYSCALLS){
		printk(K_ERR LOG_PREFIX "Syscall register id 0x%x is higher than max id 0x%x\n", id, MAX_SYSCALLS-1);
		return;
	}

	syscall_handlers[id] = handler;
	printk(K_INFO LOG_PREFIX "Registered new syscall handler with id 0x%x\n", id);
}
