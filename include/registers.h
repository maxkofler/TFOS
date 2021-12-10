#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdint.h>

typedef struct {
	
	//The data segment selector
	uint32_t	ds;

	//General purpose registers
	uint32_t	edi, esi, ebp, esp, ebx, edx, ecx, eax;

	//From isr procedure
	uint32_t	int_no, err_code;

	//Get pushed by the CPU
	uint32_t	eip, cs, eflags, eseresp, ss;

} registers_t;


#endif