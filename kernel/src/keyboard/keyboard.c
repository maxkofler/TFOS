#include "kernel/keyboard.h"

#include "kernel/io.h"
#include "kernel/monnos.h"

#include <stdint.h>

#define KEYS_SPECIAL	0x0100

//General auxiliary keys
#define KEY_ESCAPE 		0x0101
#define KEY_BACKSPACE 	0x0102
#define KEY_ENTER 		0x0103
#define KEY_SPACE		0x0104
#define KEY_L_CTRL 		0x0105
#define KEY_R_CTRL 		0x0106
#define KEY_L_SHIFT 	0x0107
#define KEY_R_SHIFT		0x0108
#define KEY_L_ALT		0x0109
#define KEY_R_ALT		0x010A
#define KEY_CAPS_LCK	0x010B
#define KEY_SCROLL_LCK	0x010C
#define KEY_NUM_LOCK	0x010D

//Function keys
#define KEY_F1			0x0110
#define KEY_F2			0x0111
#define KEY_F3			0x0112
#define KEY_F4			0x0113
#define KEY_F5			0x0114
#define KEY_F6			0x0115
#define KEY_F7			0x0116
#define KEY_F8			0x0117
#define KEY_F9			0x0118
#define KEY_F10			0x0119
#define KEY_F11			0x011A
#define KEY_F12			0x011B

//Keypad keys
#define KEYP_0			0x0120
#define KEYP_1			0x0121
#define KEYP_2			0x0122
#define KEYP_3			0x0123
#define KEYP_4			0x0124
#define KEYP_5			0x0125
#define KEYP_6			0x0126
#define KEYP_7			0x0127
#define KEYP_8			0x0128
#define KEYP_9			0x0129
#define KEYP_DOT		0x012A
#define KEYP_MINUS		0x012B
#define KEYP_PLUS		0x012C
#define KEYP_TIMES		0x012D
#define KEYP_DIV		0x012E
#define KEYP_ENTER		0x012F

static uint16_t keymap[] = {
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
	0, 0, 0, KEY_F11,							//88
	KEY_F12
};

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