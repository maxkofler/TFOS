#include "kernel/interrupts/idt_gate.h"

#define low_16(addr) (uint16_t)((addr) & 0xFFFF)
#define high_16(addr) (uint16_t)(((addr) >> 16) & 0xFFFF)


idt_gate_t idt[IDTS_REGISTERED];

void set_idt_gate(int n, uint32_t handler){
	idt[n].low_offset = low_16(handler);
	idt[n].selector = 0x08;					//GDT
	idt[n].always0 = 0;						//Is always 0
	idt[n].flags = 0x8E;					//TODO: Flags???
	idt[n].high_offset = high_16(handler);
}