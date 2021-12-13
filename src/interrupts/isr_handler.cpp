#include "registers.h"

#include "terminal.h"

extern Terminal::Terminal kernelTTY;

extern "C" void isr_handler(registers_t* r){
	kernelTTY.print("Trapped an interrupt!\n");

	for (int i = 0; i < 100000000; i++);
}