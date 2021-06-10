#ifndef __TFOS_TERMINAL__
#define __TFOS_TERMINAL__

#include "vga.h"

#include <stdint.h>
#include <stddef.h>

class Terminal{
public:
    Terminal(size_t width, size_t height, uint16_t* screenstart);

    /**
     *  Initializes the terminal, initializing VGA module
     **/
    void                                    init();

    /**
     *  Fills the entire screen with ' '
     **/
    void                                    clear();

    /**
     *  Puts the provided string to the console
     *  @arg    string                      The string to print
     **/
    void                                    print(const char* string);

    void                                    setColor(uint8_t fg, uint8_t bg){this->_vga.setColor(fg, bg);}

private:
    VGA                                     _vga;

    size_t                                  _x;
    size_t                                  _y;
};

#endif