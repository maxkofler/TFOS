#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "output/terminal.h"
 
extern "C" void kernel_main(void) 
{
	/* Initialize terminal interface 
	terminal_initialize();
 
	Newline support is left as an exercise.
	terminal_writestring("TFOS kernel\n");

	*/

	Terminal tty0(80, 25, (uint16_t*)0xB8000);

	//Set the screen size
	tty0.init();

	//Set the terminal color
	tty0.setColor(VGA::COLOR_LIGHT_GREEN, VGA::COLOR_DARK_GREY);

	//Clear the screen
	tty0.clear();

	//Write something to the terminal
	tty0.print("Hello World from C++ kernel!");

	while(1);
}