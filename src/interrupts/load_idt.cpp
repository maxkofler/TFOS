#include "interrupts/idt_register.h"
#include "interrupts/idt_gate.h"

idt_register_t idt_reg;

#include "terminal.h"
extern Terminal::Terminal kernelTTY;

void load_idt(){
	kernelTTY.print("Loading idt...\n");

	idt_reg.base = (uint32_t) &idt;
	//1 is the amount of interrupt descriptors
	idt_reg.limit = 1 * sizeof(idt_gate_t) - 1;
	asm volatile("lidt (%0)" : : "r" (&idt_reg));
}