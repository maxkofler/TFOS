#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>

#include "kernel/registers.h"

#define BIT_PRESSED			0
#define BIT_MOD_L_SHIFT 	1
#define BIT_MOD_R_SHIFT 	2
#define BIT_MOD_CAPS 		3
#define BIT_MOD_L_CTRL 		4
#define BIT_MOD_R_CTRL 		5
#define BIT_MOD_ALT			6
#define BIT_MOD_ALT_GR		7
#define BIT_MOD_SUPER		8

typedef struct {
	//The state of the key with its modifiers
	uint16_t state;
	
	//The character that was pressed in UPPERCASE
	char character;
} key_t;

void callback_key_event(registers_t*);

#endif