#include "kernel/interrupts.h"
#include "kernel/registers.h"		//CPU register struct (registers_t)
#include "kernel/utility.h"			//low_16(), high_16()

/** TODO: replace with vga_put_string() with better */
#include "kernel/vga.h"

//External function to construct the IDT
//before loading the table using load_idt()
void isr_install();

/**
 * @brief	Structure to represent an IDT gate in memory
 */
typedef struct {
	uint16_t	low_offset;
	uint16_t	selector;
	uint8_t		always0;
	uint8_t		flags;
	uint16_t	high_offset;
} __attribute__((packed)) idt_gate_t;

//The IDT itself in memory (We will load this using load_idt() into the CPU)
idt_gate_t idt[IDTS_REGISTERED];

/**
 * @brief	Structure to represent the IDT register in the CPU
 * 			This register is loaded (using "lidt") into the CPU to point to the IDT in memory
 */
typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idt_register_t;

//The register to load using load_idt()
idt_register_t idt_reg;

/**
 * @brief	Sets an IDT gate up in memory (This sets up the pointer to the interrupt handler written in assembly)
 * @param	n				The number of the interrupt service routine
 * @param	handler			The adress to the handler (assembly in kernel/interrupts/isr.asm)
 */
void set_idt_gate(int n, uint32_t handler){
	idt[n].low_offset = low_16(handler);
	idt[n].selector = 0x08;					//GDT
	idt[n].always0 = 0;						//Is always 0
	idt[n].flags = 0x8E;					//TODO: Flags???
	idt[n].high_offset = high_16(handler);
}

/**
 * @brief	The CPU uses interrupts to throw exception in protected mode,
 * 			these are the exceptions in plain text
 */
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

/**
 * @brief	Instructs the CPU to load the previously constructed
 * 			interrupt descriptor table (IDT) for interrupt handling
 */
void load_idt(){
	idt_reg.base = (uint32_t) &idt;
	//1 is the amount of interrupt descriptors
	idt_reg.limit = IDTS_REGISTERED * sizeof(idt_gate_t) - 1;
	asm volatile("lidt (%0)" : : "r" (&idt_reg));
}

/**
 * @brief	For now this is our interrupt handler, it just prints the message of the exception
 * @param	r				The registers of the CPU
 */
void isr_handler(registers_t* r){
	vga_put_string("Trapped interrupt: ");
	vga_put_string(cpu_exception_message[r->int_no]);
	vga_put_char('\n');

	for (int i = 0; i < 100000000; i++);
}

/**
 * @brief	Function for wrapping all the functionality on top
 * 			This function initializes the OSes interrupt mechanism
 * 			and registers all implemented interrupts
 */
void kernel_setup_interrupts(void){
	isr_install();
	load_idt();
}