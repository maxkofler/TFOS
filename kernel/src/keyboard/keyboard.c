#include "kernel/keyboard.h"
#include "kernel/keyboard/keymaps.h"

#include "kernel/io.h"
#include "kernel/monnos.h"

#include <stdint.h>

uint16_t* keymap = keymap_us;

/**
 * @brief	Loads the specified keyboard layout into the driver
 * @param	layout		The new layout to use
 */
void load_keymap(enum keyboard_layout layout){
	switch (layout){
		case LAYOUT_US:
			printk("KEYBOARD: Setting keyboard_layout to \"US\"\n");
			keymap = keymap_us;
			break;

		case LAYOUT_DE:
			printk("KEYBOARD: Setting keyboard_layout to \"DE\"\n");
			keymap = keymap_de;
			break;

		case LAYOUT_DEFAULT:
		default:
			printk("KEYBOARD: Defaulting to keyboard layout \"US\"\n");
			keymap = keymap_us;
	}
}

void callback_special_key(uint16_t key);

void callback_key_event(registers_t *){
	uint8_t c = inb(0x60);
	if (c > 89)
		return;

	if (keymap[c] > KEYS_SPECIAL){
		printk("Special key 0x%x\n", keymap[c]);
		callback_special_key(keymap[c]);
		return;
	}
	
	printk("%c", keymap[c]);
}

void callback_special_key(uint16_t key){
	switch (key){
		case KEY_ESCAPE:
			outw(0x604, 0x2000);
	}
}