#ifndef __IDT_GATE_H__
#define __IDT_GATE_H__

#include <stdint.h>

#define IDTS_REGISTERED 32

typedef struct {
	uint16_t	low_offset;
	uint16_t	selector;
	uint8_t		always0;
	uint8_t		flags;
	uint16_t	high_offset;
} __attribute__((packed)) idt_gate_t;

extern idt_gate_t idt[];

extern void set_idt_gate(int n, uint32_t handler);

#endif