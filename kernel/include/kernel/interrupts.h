#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <stdint.h>

#define IDTS_REGISTERED 32

/**
 * @brief	Initializes interrupts, remaps the PIC and sets up irqs TODO: irqs
 */
void kernel_setup_interrupts(void);

#endif