#include "io.h"

namespace IO{
    uint8_t inb(uint16_t port){
        uint8_t res;
        __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
        return res;
    }

    void outb(uint16_t port, uint8_t data){
        __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
    }
}