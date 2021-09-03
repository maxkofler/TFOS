#include "vga.h"

extern "C" void kernel_main(){

    int col = VGA::BLACK;
    col++;

    VGA::VGA vga;
    vga.init((uint16_t*)0xB8000, 80, 25);
    vga.setColor(VGA::WHITE, VGA::BLACK);
    vga.put(0, 0, 'H');
    vga.put(1, 0, 'i');
    vga.put(2, 0, '!');

    while(1);
}