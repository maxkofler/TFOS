#include "kernel/monnos.h"
#include "kernel/syscall.h"
#include "kernel/interrupts.h"

#define LOG_PREFIX "[ SYSCALL ] "

void syscall_int_handler(registers_t*);

void syscall_init(uint8_t int_num){
	printk(K_INFO LOG_PREFIX "Initializing syscall interface on interrupt #%i\n", int_num);

	register_int_handler(int_num, syscall_int_handler);
}

void syscall_int_handler(registers_t* registers){
	printk(K_INFO LOG_PREFIX "Received syscall with id 0x%x\n", registers->eax);
}
