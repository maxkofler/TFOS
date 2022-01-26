#include "kernel/keyboard.h"
#include "kernel/keyboard/keymaps.h"

#include "kernel/io.h"
#include "kernel/monnos.h"

#include <stdint.h>

uint16_t* keymap = keymap_us;
uint16_t* keymap_default = keymap_us;
uint16_t* keymap_shift = keymap_us_shift;
void (*special_char_callback)(uint16_t character);

/**
 * @brief	Loads the specified keyboard layout into the driver
 * @param	layout		The new layout to use
 */
void load_keymap(enum keyboard_layout layout){
	switch (layout){
		case LAYOUT_US:
			printk("KEYBOARD: Setting keyboard_layout to \"US\"\n");
			keymap = keymap_us;
			keymap_default = keymap_us;
			keymap_shift = keymap_us_shift;
			special_char_callback = special_char_us;
			break;

		case LAYOUT_DE:
			printk("KEYBOARD: Setting keyboard_layout to \"DE\"\n");
			keymap = keymap_de;
			keymap_default = keymap_de;
			keymap_shift = keymap_de_shift;
			special_char_callback = special_char_de;
			break;

		case LAYOUT_DEFAULT:
		default:
			printk("KEYBOARD: Defaulting to keyboard layout \"US\"\n");
			keymap = keymap_us;
			special_char_callback = special_char_us;
	}
}

/**
 * @brief	A handler to process key events, DO NOT CALL THIS OUTSIDE INTERRUPTS
 * @note	This is ment to get called from an interrupt because it reads from the keyboard
 * 			directly
 */
void key_event(registers_t *){
	uint8_t c = inb(0x60);

	process_keycode(c);
}

/**
 * @brief	A handler to handle common, non overridden special characters 
 * @param	c			The special character to handle
 */
void process_keycode(uint8_t keycode){
	#ifdef DEBUG_PRINT_SCANCODES
	printk("Scancode: 0x%x (%i)\n", c, c);
	#endif

	if (keycode > 89)
		return;

	uint16_t character = keymap[keycode];

	if (character > KEYS_SPECIAL){
		#ifdef DEBUG_PRINT_SPECIAL_CHAR_CODES
		printk("Special key 0x%x\n", character);
		#endif
		special_char_callback(character);
		return;
	}
	
	//TODO: Remove this
	printk("%c", character);
}


static uint8_t capslock_on = 0;
/**
 * @brief	A handler to handle common, non overridden special characters 
 * @param	c			The special character to handle
 */
void common_special_char_callback(uint16_t c){
	switch (c){
		case KEY_ESCAPE:
			//Poweroff QEMU
			outw(0x604, 0x2000);
			break; //Unnecessary here because the Computer stops, here to mute warnings

		case KEY_CAPS_LCK:
			//Switch the keymap to the shift map
			capslock_on = !capslock_on;
			if (capslock_on)
				keymap = keymap_shift;
			else
				keymap = keymap_default;
			#ifdef DEBUG_PRINT_CAPSLOCK_STATE
			printk("Capslock state: %i\n", capslock_on);
			#endif
			break;
	}
}