#include "interrupts/idt_gate.h"

#define low_16(addr) (uint16_t)((addr) & 0xFFFF)
#define high_16(addr) (uint16_t)(((addr) >> 16) & 0xFFFF)


idt_gate_t idt[256];

void set_idt_gate(int n, uint32_t handler){
	idt_gate_t* gate = &idt[n];

	gate->low_offset = low_16(handler);
	gate->selector = 0x08;	//GDT
	gate->always0 = 0;		//Is always 0
	gate->flags = 0x8E;		//TODO: Flags???
	gate->high_offset = high_16(handler);
}