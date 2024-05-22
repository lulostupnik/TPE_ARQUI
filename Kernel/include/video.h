
#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>

// Puts a pixel at the specified (x, y) coordinates with the specified color.
// hexColor: The color of the pixel in hexadecimal format.
// x: The x-coordinate of the pixel.
// y: The y-coordinate of the pixel.
void putPixel(uint8_t red, uint8_t green, uint8_t blue, uint64_t x, uint64_t y);
void putRectangle(uint8_t red, uint8_t green, uint8_t blue, uint64_t x, uint64_t y, uint64_t width, uint64_t height);
void drawLetter(uint64_t x, uint64_t y, char ascii);

void drawString(uint64_t x, uint64_t y, char *string);

void clearScreen();
#endif // VIDEODRIVER_H