#ifndef __VGA_H__
#define __VGA_H__

#include <stdint.h>
#include <stddef.h>

class VGA{
public:
    VGA();
    VGA(size_t width, size_t height, uint16_t* screenStart);

    /**
     *  Sets the terminal color
     *  @arg    fg                          Foreground
     *  @arg    bg                          Background
     **/
    void                                    setColor(uint8_t fg, uint8_t bg);

    /**
     *  Returns a VGA entry containing the color and the character
     *  @arg    character                   The caracter to pair with the color
     **/
    void                                    putCharAt(size_t x, size_t y, unsigned char character);

    size_t      getWidth(){return this->_width;}
    size_t      getHeight(){return this->_height;}

    enum color{
        COLOR_BLACK = 0,
        COLOR_BLUE = 1,
        COLOR_GREEN = 2,
        COLOR_CYAN = 3,
        COLOR_RED = 4,
        COLOR_MAGENTA = 5,
        COLOR_BROWN = 6,
        COLOR_LIGHT_GREY = 7,
        COLOR_DARK_GREY = 8,
        COLOR_LIGHT_BLUE = 9,
        COLOR_LIGHT_GREEN = 10,
        COLOR_LIGHT_CYAN = 11,
        COLOR_LIGHT_RED = 12,
        COLOR_LIGHT_MAGENTA = 13,
        COLOR_LIGHT_BROWN = 14,
        COLOR_WHITE = 15,
    };

private:
    uint8_t                                 _curColor;
    uint16_t*                               _screenStart;

    size_t                                  _width;
    size_t                                  _height;
};

#endif