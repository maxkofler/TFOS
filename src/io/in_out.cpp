#include "io.h"

namespace IO{
    uint8_t in(uint16_t port){
        uint8_t res;
        __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
        return res;
    }

    void out(uint16_t port, uint8_t data){
        __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
    }
}