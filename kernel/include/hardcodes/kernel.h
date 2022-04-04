#ifndef __HARDCODE_KERNEL_H__
#define __HARDCODE_KERNEL_H__

#define KERNEL_LEN_ADDR 0x7c02

//	0 - 0xfe	BIOS disk number
//	255			Already loaded by chainload
#define KERNEL_LOAD_SOURCE 0x7c03

#endif
