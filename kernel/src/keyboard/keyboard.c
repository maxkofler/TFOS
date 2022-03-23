#include "kernel/keyboard.h"
#include "kernel/keyboard/keymaps.h"

#include "kernel/io.h"
#include "kernel/monnos.h"

#include <stdint.h>

#define LOG_PREFIX "[KBRD ] "

uint16_t* keymap = keymap_us;
uint16_t* keymap_default = keymap_us;
uint16_t* keymap_shift = keymap_us_shift;
void (*special_char_callback)(uint16_t character);

void char_callback(uint16_t c);

/**
 * @brief	Loads the specified keyboard layout into the driver
 * @param	layout		The new layout to use
 */
void load_keymap(enum keyboard_layout layout){
	switch (layout){
		case LAYOUT_US:
			printk(K_INFO LOG_PREFIX "KEYBOARD: Setting keyboard_layout to \"US\"\n");
			keymap = keymap_us;
			keymap_default = keymap_us;
			keymap_shift = keymap_us_shift;
			special_char_callback = special_char_us;
			break;

		case LAYOUT_DE:
			printk(K_INFO LOG_PREFIX "KEYBOARD: Setting keyboard_layout to \"DE\"\n");
			keymap = keymap_de;
			keymap_default = keymap_de;
			keymap_shift = keymap_de_shift;
			special_char_callback = special_char_de;
			break;

		case LAYOUT_DEFAULT:
		default:
			printk(K_INFO LOG_PREFIX "KEYBOARD: Defaulting to keyboard layout \"US\"\n");
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
	printk(K_DEBUG "Scancode: 0x%x (%i)\n", keycode, keycode);
	#endif

	uint16_t mask_pressed = 0;

	if (keycode >= 0x80){
		#ifdef DEBUG_PRINT_RELEASES
		printk(K_DEBUG LOG_PREFIX "Released key, shifting scancode 0x%x down by 0x80\n", keycode);
		#endif
		keycode -= 0x80;
		mask_pressed = (1 << BIT_PRESSED);
		#ifdef DEBUG_PRINT_SCANCODES
		printk(K_DEBUG LOG_PREFIX "Scancode after key release shifting: 0x%x (%i) = '%c'\n", keycode, keycode, keymap[keycode]);
		#endif
	}

	uint16_t character = keymap[keycode];

	character |= mask_pressed;

	//KEYS_SPECIAL is defined BEFORE the first special key, so we can handle it like this
	if (character > KEYS_SPECIAL){
		#ifdef DEBUG_PRINT_SPECIAL_CHAR_CODES
		printk(K_DEBUG LOG_PREFIX "Special key 0x%x\n", character);
		#endif
		special_char_callback(character);
		return;
	}

	//Else call a default callback
	char_callback(character);
	
	//TODO: Remove this
	//printk("%c", character);
}


static uint8_t capslock_on = 0;
static uint8_t shift_on = 0;
/**
 * @brief	A handler to handle common, non overridden special characters 
 * @param	c			The special character to handle
 */
void common_special_char_callback(uint16_t c){
	uint16_t c_switch = c;

	if ((c >> BIT_PRESSED) & 1){
		c_switch -= (1 << BIT_PRESSED);
	}
	
	switch (c_switch){
		case KEY_ESCAPE:
			//Poweroff QEMU
			outw(0x604, 0x2000);
			printk(K_INFO LOG_PREFIX "Turning off machine!\n");
			break; //Unnecessary here because the Computer stops, here to mute warnings

		case KEY_CAPS_LCK:
			//Switch the keymap to the shift map
			capslock_on = !capslock_on;
			if (capslock_on)
				keymap = keymap_shift;
			else
				keymap = keymap_default;
			#ifdef DEBUG_PRINT_CAPSLOCK_STATE
			printk(K_DEBUG LOG_PREFIX "Capslock state: %i\n", capslock_on);
			#endif
			break;

		case KEY_SPACE:
			if (!((c >> BIT_PRESSED) & 1))
				printk(" ");
			break;

		case KEY_ENTER:
			if (!((c >> BIT_PRESSED) & 1))
				printk("\n");
			break;
		
		case KEY_BACKSPACE:
			if (!((c >> BIT_PRESSED) & 1))
				printk("\b \b");
			break;

		case KEY_L_SHIFT:
		case KEY_R_SHIFT:
			shift_on = !((c >> BIT_PRESSED) & 1);
			if (shift_on)
				keymap = keymap_shift;
			else
				keymap = keymap_default;
			#ifdef DEBUG_PRINT_SHIFT_STATE
			printk(K_DEBUG LOG_PREFIX "Shift state: %i\n", shift_on);
			#endif
			break;
	}
}

void char_callback(uint16_t c){
	if (c > 0x80)
		return;

	printk("%c", c);
}