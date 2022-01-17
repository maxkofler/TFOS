
#include "kernel/vga.h"
#include "kernel/interrupts.h"

#include "kernel/io.h"

void vga_char(uint16_t pos, uint8_t c);

/**
 * @brief	This is the kernel entry point, the kernel never returns,
 * 			hence the loop at the end
 */
void kernel_main(void){
	vga_setup();

	vga_put_string("Welcome to TFOS! No warranty is provided!\n>>>");

	kernel_setup_interrupts();

	asm("int $9");

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