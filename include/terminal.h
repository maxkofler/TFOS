#ifndef __TERMINAL_H__
#define __TERMINAL_H__

namespace Terminal{
    class Terminal;
}

#include "vga.h"

namespace Terminal{
    class Terminal{
    public:
        void                            setVGA(VGA::VGA *vga);
        void                            setSize(uint16_t w, uint16_t h);

        void                            print(char c);
        void                            print(const char *msg);

        void                            setCursor(uint16_t x, uint16_t y);


    private:
        VGA::VGA*                       _vga;

        uint16_t                        _cursor_pos = 0;
    };
}

#endif