#include "vga.h"
#include "terminal.h"

Terminal::Terminal kernelTTY;

void isr_install();

extern "C" void kernel_main(){

    int col = VGA::BLACK;
    col++;

    VGA::VGA vga((uint16_t*)0xB8000, 80, 25);
    vga.setColor(VGA::WHITE, VGA::BLACK);
    vga.enableCursor(14, 15);
    vga.clear();

    kernelTTY.setVGA(&vga);
    kernelTTY.setCursor(0, 0);

    kernelTTY.print("Assembling isrs...\n");

	isr_install();

	kernelTTY.print("Enabling external interrupts\n");
	asm volatile("sti");

    kernelTTY.print("No warranty is provided, use this at your own risk!\n");
    kernelTTY.print(">");

    //asm volatile ("1: jmp 1b");
    //asm volatile("int 3");
    for (int i = 0; i < 10000000; i++);
    
    //int nul = 0 / 0;
    //asm volatile ("1: jmp 1b");

    while(1);
}