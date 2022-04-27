#include "kernel/monnos.h"
#include "kernel/syscall.h"
#include "kernel/interrupts.h"
#define LOG_PREFIX LOG_PREFIX_SCALL

#include <stddef.h>

//Array containing all the syscall pointers
void (*syscall_handlers[MAX_SYSCALLS])(registers_t*);

void syscall_int_handler(registers_t*);

void syscall_init(uint8_t int_num){
	printk(K_INFO LOG_PREFIX "Initializing syscall interface on interrupt #%i\n", int_num);

	register_int_handler(int_num, syscall_int_handler);

	//Reset all syscall handlers
	for (syscall_id i = 0; i < MAX_SYSCALLS; i++){
		syscall_handlers[i] = NULL;
	}
}

void syscall_int_handler(registers_t* registers){
	printk(K_INFO LOG_PREFIX "Received syscall with id 0x%x\n", registers->eax);

	syscall_id id = registers->eax;

	if (id >= MAX_SYSCALLS){
		printk(K_ERR LOG_PREFIX "Called syscall with id 0x%x is higher than max id 0x%x\n", id, MAX_SYSCALLS-1);
		return;
	}

	if (syscall_handlers[id] == NULL){
		printk(K_ERR LOG_PREFIX "Called syscall with id 0x%x is not registered\n", id);
		return;
	}

	syscall_handlers[id](registers);
}
