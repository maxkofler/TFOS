#include "kernel/keyboard/keymaps.h"
#include "kernel/keyboard.h"

uint16_t keymap_de[] = {
	0, KEY_ESCAPE, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	's', '`', KEY_BACKSPACE, '\t',
	'q', 'w', 'e', 'r',	
	't', 'z', 'u', 'i',
	'o', 'p', 'u', '+',
	KEY_ENTER, KEY_L_CTRL, 'a', 's',
	'd', 'f', 'g', 'h',		
	'j', 'k', 'l', 'o',
	'a', '<', KEY_L_SHIFT, '#',
	'y', 'x', 'c', 'v',
	'b', 'n', 'm', ',',
	'.', '-', KEY_R_SHIFT, KEYP_TIMES,
	KEY_L_ALT, KEY_SPACE, KEY_CAPS_LCK, KEY_F1,
	KEY_F2, KEY_F3, KEY_F4, KEY_F5,
	KEY_F6, KEY_F7, KEY_F8, KEY_F9,
	KEY_F10, KEY_NUM_LOCK, KEY_SCROLL_LCK, KEYP_7,
	KEYP_8, KEYP_9, KEYP_MINUS, KEYP_4,
	KEYP_5, KEYP_6, KEYP_PLUS, KEYP_1,
	KEYP_2, KEYP_3, KEYP_4, KEYP_0, KEYP_DOT,
	0, '<', 0, KEY_F11,
	KEY_F12//89
};

uint16_t keymap_de_shift[] = {
	0, KEY_ESCAPE, '!', '\"',
	'?', '$', '%', '&',			// TODO: '?' should be '§'
	'/', '(', ')', '=',
	'?', '`', KEY_BACKSPACE, '\t',
	'Q', 'W', 'E', 'R',	
	'T', 'Z', 'U', 'I',
	'O', 'P', 'U', '+',
	KEY_ENTER, KEY_L_CTRL, 'A', 'S',
	'D', 'F', 'G', 'H',		
	'J', 'K', 'L', 'O',
	'A', '<', KEY_L_SHIFT, '\'',
	'Y', 'X', 'C', 'V',
	'B', 'N', 'M', ';',
	':', '_', KEY_R_SHIFT, KEYP_TIMES,
	KEY_L_ALT, KEY_SPACE, KEY_CAPS_LCK, KEY_F1,
	KEY_F2, KEY_F3, KEY_F4, KEY_F5,
	KEY_F6, KEY_F7, KEY_F8, KEY_F9,
	KEY_F10, KEY_NUM_LOCK, KEY_SCROLL_LCK, KEYP_7,
	KEYP_8, KEYP_9, KEYP_MINUS, KEYP_4,
	KEYP_5, KEYP_6, KEYP_PLUS, KEYP_1,
	KEYP_2, KEYP_3, KEYP_4, KEYP_0, KEYP_DOT,
	0, '>', 0, KEY_F11,
	KEY_F12//89
};

void special_char_de(uint16_t c){
	common_special_char_callback(c);
}