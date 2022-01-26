#include "kernel/keyboard/keymaps.h"
#include "kernel/keyboard.h"

uint16_t keymap_us[] = {
	0, KEY_ESCAPE, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	'-', '=', KEY_BACKSPACE, '\t',
	'Q', 'W', 'E', 'R',	
	'T', 'Y', 'U', 'I',
	'O', 'P', '[', ']',
	KEY_ENTER, KEY_L_CTRL, 'A', 'S',
	'D', 'F', 'G', 'H',		
	'J', 'K', 'L', ';',
	'\'', '`', KEY_L_SHIFT, '\\',
	'Z', 'X', 'C', 'V',
	'B', 'N', 'M', ',',
	'.', '/', KEY_R_SHIFT, KEYP_TIMES,
	KEY_L_ALT, KEY_SPACE, KEY_CAPS_LCK, KEY_F1,
	KEY_F2, KEY_F3, KEY_F4, KEY_F5,
	KEY_F6, KEY_F7, KEY_F8, KEY_F9,
	KEY_F10, KEY_NUM_LOCK, KEY_SCROLL_LCK, KEYP_7,
	KEYP_8, KEYP_9, KEYP_MINUS, KEYP_4,
	KEYP_5, KEYP_6, KEYP_PLUS, KEYP_1,
	KEYP_2, KEYP_3, KEYP_4, KEYP_0, KEYP_DOT,
	0, 0, 0, KEY_F11,
	KEY_F12//89
};