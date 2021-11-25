#include "vga.h"
#include "terminal.h"

extern "C" void kernel_main(){

    int col = VGA::BLACK;
    col++;

    VGA::VGA vga((uint16_t*)0xB8000, 80, 25);
    vga.setColor(VGA::WHITE, VGA::BLACK);
    vga.enableCursor(14, 15);
    vga.clear();

    Terminal::Terminal tty;
    tty.setVGA(&vga);
    tty.setCursor(0, 0);
    tty.print("No warranty is provided, use this at your own risk!\n");
    tty.print(">");

    while(1);
}