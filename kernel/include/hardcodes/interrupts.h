#ifndef __HARDCODE_INTERRUPTS_H__
#define __HARDCODE_INTERRUPTS_H__

//Ports for the primary PIC
#define PIC1_COMM 0x20
#define PIC1_DATA 0x21
#define PIC1_IDT_OFFSET 0x20	//Interrupt #32 is the first for PIC1
#define PIC1_ICW3 0x04			//Accepts PIC2 interrupts on irq 2

//Ports for the secondary PIC
#define PIC2_COMM 0xA0
#define PIC2_DATA 0xA1
#define PIC2_IDT_OFFSET 0x28	//Interrupt #40 is the first for PIC2
#define PIC2_ICW3 0x02			//Put PIC2 into secondary mode

//Common for both PICs
#define PIC_MODE 0x01			//8086 mode for PIC
#define PIC_ICW1 0x11			//Put the PIC into programming mode

#endif