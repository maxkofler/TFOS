#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

namespace IO{
    uint8_t in(uint16_t port);
    void out(uint16_t port, uint8_t data);
}

#endif