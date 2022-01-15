#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__("inb %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t result;
    __asm__("inw %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

static inline void outb(uint16_t port, uint8_t data) {
    __asm__("outb %%al, %%dx" : : "a" (data), "d" (port));
}

static inline void outw(uint16_t port, uint16_t data) {
    __asm__("outw %%ax, %%dx" : : "a" (data), "d" (port));
}

#endif