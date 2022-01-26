
#include "kernel/vga.h"
#include "kernel/interrupts.h"

#include "kernel/io.h"
#include "kernel/monnos.h"
#include "kernel/keyboard.h"

#include "kernel/string.h"

void keyboard_handler(registers_t *);
void timer_handler(registers_t *);

/**
 * @brief	This is the kernel entry point, the kernel never returns,
 * 			hence the loop at the end. The control gets put to events for now, 
 * 			so this function enables external interrupts and puts the OS to sleep
 * 			until an interrupt raises, it then processes it in the handler, works
 * 			and then returns to the loop "while (1)", where it halts itself again,
 *			over and over again, this presents the kernel as a "service" to use 			
 */
void kernel_main(void){
	vga_setup();

	printk("MONNOS, press ESC to quit\n\n");

	load_keymap(LAYOUT_DE);

	kernel_setup_interrupts();

	register_int_handler(33, callback_key_event);

	//Give control to the interrupts
	asm volatile("sti");

	//If an interrupt ends, halt the CPU again
	while (1)
		asm volatile ("hlt");

	outw(0x604, 0x2000);
}