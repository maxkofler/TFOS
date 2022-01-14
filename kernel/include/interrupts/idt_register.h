#ifndef __IDT_REGISTER_H__
#define __IDT_REGISTER_H__

#include <stdint.h>

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idt_register_t;/*  */

#endif