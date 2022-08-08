#ifndef __HARDCODE_SERIAL_H__
#define __HARDCODE_SERIAL_H__

#define SERIAL_REG_DLAB_DLL 0	//(DLAB) Divisor Latch Low Byte
#define SERIAL_REG_DLAB_DLH 1	//(DLAB) Divisor Latch High Byte

#define SERIAL_REG_W_THB 0		//(w) 	Transmitter Holding Buffer
#define SERIAL_REG_R_RB 0		//(r) 	Receiver Buffer
#define SERIAL_REG_IER 1		//		Interrupt Enable Register
#define SERIAL_REG_R_IIR 2		//(r) 	Interrupt Indetifiction Register
#define SERIAL_REG_W_FCR 2		//(w) 	FIFO Control Register
#define SERIAL_REG_LCR 3		//		Line Control Register
#define SERIAL_REG_MCR 4		//		Modem Control Register
#define SERIAL_REG_R_LSR 5		//(r)	Line Status Register
#define SERIAL_REG_R_MSR 6		//(r)	Modem Status Register
#define SERIAL_REG_SR 7			//		Scratch Register

#define SERIAL_INT_DA 0			//Data available
#define SERIAL_INT_TE 1			//Transmitter empty
#define SERIAL_INT_BE 2			//Break / error
#define SERIAL_INT_SC 3			//Status change

#define SERIAL_MCR_DTR 0		//Data Terminal Ready
#define SERIAL_MCR_RTS 1		//Request to Send
#define SERIAL_MCR_OUT1 2		//OUT 1
#define SERIAL_MCR_OUT2 3		//OUT 2
#define SERIAL_MCR_LOOP 4		//Local loopback (for testing)

#define SERIAL_LCR_SB 2			//Stop bits (0 = One Stop bit, 1 = 1.5 / 2 Stop bits)
#define SERIAL_LCR_SBE 6		//Set Break Enable
#define SERIAL_LCR_DLAB 7		//Divisor Latch Access Bit (DLAB)

#define SERIAL_LSR_DR 0			//Data ready
#define SERIAL_LSR_OE 1			//Overrun error (lost data)
#define SERIAL_LSR_PE 2			//Parity error
#define SERIAL_LSR_FE 3			//Framing error (missing stop bit)
#define SERIAL_LSR_BI 4			//Break indicator
#define SERIAL_LSR_THRE 5		//Transmitter holding register (data can be sent)
#define SERIAL_LSR_TEMT 6		//Transmitter empty
#define SERIAL_LSR_IE 7			//Impending error (some error with a word in buffer)

#define SERIAL_MSR_DCTS 0		//Delta Clear to Send
#define SERIAL_MSR_DDSR	1		//Delta Data Set Ready
#define SERIAL_MSR_TERI	2		//Trailing Edge of Ring Indicator
#define SERIAL_MSR_DDCD	3		//Delta Data Carrier Detect
#define SERIAL_MSR_CTS 4		//Clear to Send
#define SERIAL_MSR_DSR 5		//Data Set Ready
#define SERIAL_MSR_RI 6			//Ring Indicator
#define SERIAL_MSR_DCD 7		//Data Carrier Detect

enum serial_divisor{
	BAUD_50 = 2304,
	BAUD_110 = 1047,
	BAUD_220 = 524,
	BAUD_300 = 384,
	BAUD_600 = 192,
	BAUD_1200 = 96,
	BAUD_2400 = 48,
	BAUD_4800 = 24,
	BAUD_9600 = 12,
	BAUD_19200 = 6,
	BAUD_38400 = 3,
	BAUD_57600 = 2,
	BAUD_115200 = 1
};

#define SERIAL_1_PORT 0x3F8		//The base address for COM1
#define SERIAL_1_IRQ 4			//The IRQ assigned with COM1

#define SERIAL_2_PORT 0x2F8		//The base address for COM1
#define SERIAL_2_IRQ 3			//The IRQ assigned with COM1

#endif
