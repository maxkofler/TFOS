#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"
 
extern "C" void kernel_main(void) 
{
	/* Initialize terminal interface 
	terminal_initialize();
 
	Newline support is left as an exercise.
	terminal_writestring("TFOS kernel\n");

	*/

	VGA vga;

	vga.i++;

	while(1);
}