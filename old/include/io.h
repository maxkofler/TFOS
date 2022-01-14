#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

namespace IO{
	/**
	 * @brief	Reads a byte from the specified port of the cpu
	 * @param	port			The port to read from
	 * @return	The byte read
	 */
	uint8_t						inb(uint16_t port);

	/**
	 * @brief	Writes a byte to the specified port of the cpu
	 * @param	port			The port to write to
	 * @param	data			The data byte to write
	 */
	void						outb(uint16_t port, uint8_t data);
}

#endif
