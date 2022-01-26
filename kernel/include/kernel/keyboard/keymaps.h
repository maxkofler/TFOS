#ifndef __KEYMAPS_H__
#define __KEYMAPS_H__

#include <stdint.h>

//A pointer to the US keyboard map
extern uint16_t keymap_us[];
extern uint16_t keymap_us_shift[];
void special_char_us(uint16_t character);

//A pointer to the DE keyboard map
extern uint16_t keymap_de[];
extern uint16_t keymap_de_shift[];
void special_char_de(uint16_t character);

#endif