#include <video.h>

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;

extern uint8_t font_bitmap[256][16];

/*
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}
*/



/**
 * @brief Draws a letter at the specified (x, y) coordinates with the specified RGB color.
 *
 * @param x The x-coordinate of the top-left corner of the letter.
 * @param y The y-coordinate of the top-left corner of the letter.
 * @param ascii The ASCII value of the letter to be drawn.
 */
void drawLetter(uint64_t x, uint64_t y, char ascii) {
    uint8_t *letter = font_bitmap[(uint8_t)ascii];
    for (uint64_t i = 0; i < 16; i++) {
        for (uint64_t j = 0; j < 8; j++) {
            if ((letter[i] >> j) & 0x1) {
                putPixel(255, 255, 255, x + j, y + i);
            }
        }
    }
}

/**
 * Puts a pixel at the specified (x, y) coordinates with the specified RGB color.
 * @param red: The red component of the pixel color.
 * @param green: The green component of the pixel color.
 * @param blue: The blue component of the pixel color.
 * @param x: The x-coordinate of the pixel.
 * @param y: The y-coordinate of the pixel.
 */
void putPixel(uint8_t red, uint8_t green, uint8_t blue, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  blue;
    framebuffer[offset+1]   =  green;
    framebuffer[offset+2]   =  red;
}




/**
 * @brief Draws a rectangle with the specified color, position and size.
 *
 * @param red The red component of the rectangle color.
 * @param green The green component of the rectangle color.
 * @param blue The blue component of the rectangle color.
 * @param x The x-coordinate of the rectangle.
 * @param y The y-coordinate of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 */

void drawRectangle(uint8_t red, uint8_t green, uint8_t blue, uint64_t x, uint64_t y, uint64_t width, uint64_t height) {
    for (uint64_t i = 0; i < width; i++) {
        for (uint64_t j = 0; j < height; j++) {
            putPixel(red, green, blue, x + i, y + j);
        }
    }
}


