
#include "kernel/vga.h"
#include "kernel/interrupts.h"

#include "kernel/io.h"

void keyboard_handler(registers_t *);
void timer_handler(registers_t *);

/**
 * @brief	This is the kernel entry point, the kernel never returns,
 * 			hence the loop at the end
 */
void kernel_main(void){
	vga_setup();

	vga_put_string("Welcome to TFOS! No warranty is provided!\n>>>");

	kernel_setup_interrupts();

	register_int_handler(32, timer_handler);
	register_int_handler(33, keyboard_handler);

	asm volatile("sti");

	for (uint8_t i = 0; i < 11; i++){
		for(uint32_t n = 0; n < 0xFFFFFFF; n++);
		vga_put_char('\n');
		vga_put_char('0'+i);
		vga_put_string("/10");
		vga_put_char('\n');
	}

	//QEMU command for shutdown
	outw(0x604, 0x2000);

}

void timer_handler(registers_t *){

}

void keyboard_handler(registers_t *){	
	char c = inb(0x60);
	vga_put_string("Keycode: \"");
	vga_put_char(c);
	vga_put_string("\"\n");

}