#include "kernel/registers.h"

#include "kernel/vga.h"

const char *cpu_exception_message[] = {
	"Division by zero",
	"Debug",
	"Non maskable interrupt",
	"Breakpoint (INT 3)",
	"Overflow (INTO)",
	"Bounds check (BOUND)",
	"Invalid opcode",
	"Coprocessor not available",
	"Double fault",
	"(reserved)",
	"Invalid TSS",
	"Segment not present",
	"Stack exception",
	"General protection",
	"Page fault",
	"(reserved)",
	"Coprocessor error"
};

void isr_handler(registers_t* r){
	vga_put_string("Trapped interrupt: ");
	vga_put_string(cpu_exception_message[r->int_no]);
	vga_put_char('\n');

	for (int i = 0; i < 100000000; i++);
}