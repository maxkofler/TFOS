#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stdint.h>

#include "hardcodes/hc_serial.h"

/**
 * @brief	Sets the serial chips clock divisor latch value to
 * 			set the BAUD rate
 * @param	base_port			The IO port the UART chip is found at
 * @param	divisor				The divisor value
 */
void serial_set_divisor(uint16_t base_port, uint16_t divisor);

/**
 * @brief	Returns the serial chips clock divisor latch value
 * @param	base_port			The IO port the UART chip is found at
 * @return	uint16_t
 */
uint16_t serial_get_divisor(uint16_t base_port);

/**
 * @brief	Sets a specific bit in the serial chip
 * @param	base_port			The IO port the UART chip is found at
 * @param	reg_offset			The register offset from the base port
 * @param	bit_pos				The position of the bit to change
 * @param	state				The state to set the bit to (0 = 0 ; >= 0 = 1)
 */
void serial_set_reg_bit(uint16_t base_port, uint8_t reg_offset, uint8_t bit_pos, uint8_t state);

/**
 * @brief	Initializes the serial port to a default state for this kernel:
 * 			- No interrupts
 * 			- Baudrate at 115200 (no divisor)
 * 			- 8 bits, no parity, no stop bit
 * 			Tests the serial chip
 * @param	base_port			The IO port the UART chip is found at
 * @return	int					0 if ok, 1 if the chip is faulty
 */
int serial_init(uint16_t base_port);

#endif
