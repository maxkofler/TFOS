#include "kernel/interrupts/idt_register.h"
#include "kernel/interrupts/idt_gate.h"

idt_register_t idt_reg;

void load_idt(){
	idt_reg.base = (uint32_t) &idt;
	//1 is the amount of interrupt descriptors
	idt_reg.limit = IDTS_REGISTERED * sizeof(idt_gate_t) - 1;
	asm volatile("lidt (%0)" : : "r" (&idt_reg));
}