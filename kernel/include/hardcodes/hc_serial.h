#ifndef __HARDCODE_COM_H__
#define __HARDCODE_COM_H__

#define SERIAL_INT_DA 0			//Data available
#define SERIAL_INT_TE 1			//Transmitter empty
#define SERIAL_INT_BE 2			//Break / error
#define SERIAL_INT_SC 3			//Status change

#define SERIAL_MCR_DTR 0		//Data Terminal Ready
#define SERIAL_MCR_RTS 1		//Request to Send
#define SERIAL_MCR_OUT1 2		//OUT 1
#define SERIAL_MCR_OUT2 3		//OUT 2
#define SERIAL_MCR_LOOP 4		//Local loopback (for testing)

#define SERIAL_LSR_DR 0			//Data ready
#define SERIAL_LSR_OE 1			//Overrun error (lost data)
#define SERIAL_LSR_PE 2			//Parity error
#define SERIAL_LSR_FE 3			//Framing error (missing stop bit)
#define SERIAL_LSR_BI 4			//Break indicator
#define SERIAL_LSR_THRE 5		//Transmitter holding register (data can be sent)
#define SERIAL_LSR_TEMT 6		//Transmitter empty
#define SERIAL_LSR_IE 7			//Impending error (some error with a word in buffer)

#define COM_1_PORT 0x3F8
#define COM_2_PORT 0x2F8

#endif
