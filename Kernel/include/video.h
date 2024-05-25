
#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>

// Puts a pixel at the specified (x, y) coordinates with the specified color.
// hexColor: The color of the pixel in hexadecimal format.
// x: The x-coordinate of the pixel.
// y: The y-coordinate of the pixel.

uint64_t drawLetter(uint64_t x, uint64_t y, char ascii, uint64_t fontSize);
uint64_t putPixel(uint8_t red, uint8_t green, uint8_t blue, uint64_t x, uint64_t y);
uint64_t putRectangle(uint8_t red, uint8_t green, uint8_t blue, uint64_t x, uint64_t y, uint64_t width, uint64_t height);



#endif // VIDEODRIVER_H