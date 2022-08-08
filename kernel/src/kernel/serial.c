#include "kernel/serial.h"

#include "kernel/io.h"

#include "kernel/monnos.h"

void serial_set_divisor(uint16_t base, uint16_t divisor){
	//Calculathe the DLL and DLH register values
	uint8_t dll = divisor & 0xFF;
	uint8_t dlh = (divisor >> 8) & 0xFF;

	//Log this change in the kernel log
	printk(K_DEBUG "[SER  ] " "Setting serial DLAB at 0x%x to %i (DLH = 0x%x, DLL = 0x%x)\n", base, divisor, dlh, dll);

	uint8_t lcr = inb(base + SERIAL_REG_LCR);		//Get the contents of the LCR register
	lcr |= 1 << SERIAL_LCR_DLAB;					//Set the DLAB bit in the LCR register
	outb(base + SERIAL_REG_LCR, lcr);				//Set the new LCR register

	//Set the new register values
	outb(base + SERIAL_REG_DLAB_DLL, dll);
	outb(base + SERIAL_REG_DLAB_DLH, dlh);

	//Restore old LCR contents with the DLAB bit unset
	lcr &= ~(1 << SERIAL_LCR_DLAB);					//Turn of the DLAB bit
	outb(base + SERIAL_REG_LCR, lcr);				//Restore the old LCR register
}
