#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <stdint.h>
#include "kernel/registers.h"

#define IDTS_REGISTERED 48

/**
 * @brief	Initializes interrupts, remaps the PIC and sets up irqs TODO: irqs
 */
void kernel_setup_interrupts(void);

/**
 * @brief	Registers an interrupt handler for the specified interrupt number
 * @param	num			The nummer of the interrupt
 * @param	handler		A function pointer to the handler function
 */
void register_int_handler(uint8_t num, void (*handler)(registers_t*));

#endif