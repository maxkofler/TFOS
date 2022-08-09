#include "kernel/serial.h"

#include "kernel/io.h"

#include "kernel/monnos.h"

void serial_set_divisor(uint16_t base, uint16_t divisor){
	//Calculathe the DLL and DLH register values
	uint8_t dll = divisor & 0xFF;
	uint8_t dlh = (divisor >> 8) & 0xFF;

	//Log this change in the kernel log
	printk(K_DEBUG "[SER  ] " "Setting DLAB at 0x%x to 0x%x (%i) (DLH = 0x%x, DLL = 0x%x)\n", base, divisor, divisor, dlh, dll);

	//Set the DLAB bit to enable divisor access
	serial_set_reg_bit(base, SERIAL_REG_LCR, SERIAL_LCR_DLAB, 1);

	//Set the new register values
	outb(base + SERIAL_REG_DLAB_DLL, dll);
	outb(base + SERIAL_REG_DLAB_DLH, dlh);

	//Unset the DLAB bit
	serial_set_reg_bit(base, SERIAL_REG_LCR, SERIAL_LCR_DLAB, 0);
}

uint16_t serial_get_divisor(uint16_t base){
	//Set the DLAB bit to enable divisor access
	serial_set_reg_bit(base, SERIAL_REG_LCR, SERIAL_LCR_DLAB, 1);

	//Set the new register values
	uint8_t dll = inb(base + SERIAL_REG_DLAB_DLL);
	uint8_t dlh = inb(base + SERIAL_REG_DLAB_DLH);

	//Unset the DLAB bit
	serial_set_reg_bit(base, SERIAL_REG_LCR, SERIAL_LCR_DLAB, 0);

	uint16_t res = 0;
	res |= dll;
	res |= dlh << 8;

	return res;
}

void serial_set_reg_bit(uint16_t base_port, uint8_t reg_offset, uint8_t bit_pos, uint8_t state){
	uint16_t port = base_port + reg_offset;

	uint8_t reg = inb(port);

	if (state)
		reg |= (1 << bit_pos);
	else
		reg &= ~(1 << bit_pos);

	outb(port, reg);
}
