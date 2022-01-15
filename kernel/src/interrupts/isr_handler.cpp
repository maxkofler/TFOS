#include "registers.h"
#include "terminal.h"

extern Terminal::Terminal kernelTTY;

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

extern "C" void isr_handler(registers_t* r){
	kernelTTY.print("Trapped an interrupt: ");
	kernelTTY.print(cpu_exception_message[2][0]);
	kernelTTY.print(cpu_exception_message[2][1]);
	kernelTTY.print(", ");
	kernelTTY.print((char)(r->int_no+'0'));
	kernelTTY.print("\n");

	for (int i = 0; i < 100000000; i++);
}