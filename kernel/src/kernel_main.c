
#include "kernel/vga.h"

void vga_char(uint16_t pos, uint8_t c);

/**
 * @brief	This is the kernel entry point, the kernel never returns,
 * 			hence the loop at the end
 */
void kernel_main(void){
	vga_setup();

	vga_put_string("Welcome to TFOS! No warranty is provided!\n>>>");

	while(1);
}