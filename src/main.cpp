#include "vga.h"
#include "terminal.h"

extern "C" void kernel_main(){

    int col = VGA::BLACK;
    col++;

    VGA::VGA vga((uint16_t*)0xB8000, 80, 25);
    vga.setColor(VGA::WHITE, VGA::BLACK);
    vga.clear();

    Terminal::Terminal tty;
    tty.setVGA(&vga);
    tty.print("TFOS>>>");

    while(1);
}