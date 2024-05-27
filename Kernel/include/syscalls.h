#include <video.h> // para las estructuras
#ifndef _SYSCALLS_H
#define _SYSCALLS_H
#include <stdint.h>
#include <stddef.h> // lo necesitamos para size_t

// @TODO: Estamos poniendo los mismos prototipos que linux

//@COMMENT: Puse los prototipos de las funciones que hice yo, no me mates Mati -Fede


uint64_t sysRead(uint64_t * toBuffer, uint64_t toBufferDim);
//uint64_t sysWrite(uint64_t x, uint64_t y, uint8_t * string);

/**
 * @brief Writes a specified number of characters from a buffer to a file descriptor.
 *
 * This system call writes 'amount' number of characters from the buffer pointed to by 'buffer' to the file descriptor 'fd'.
 * It is typically used to write output to the standard output (STDOUT) or standard error (STDERR), but can be used with any valid file descriptor. (For now it only allows STDOUT and writes directly on the screen)
 *
 * @param fd The file descriptor to which to write. This is typically STDOUT or STDERR.
 * @param buffer A pointer to a buffer containing the characters to write.
 * @param amount The number of characters to write to the file descriptor.
 * @return int64_t Returns the number of characters actually written. This may be less than 'amount' if there was an error writing to the file descriptor (or '\0' is encountered?)
 *                 Returns -1 if an error occurred (for example, if 'fd' is not a valid file descriptor).
 */

int64_t sys_write(uint64_t fd, const char * buffer, int64_t amount);

/**
 * @brief Sets the system font size.
 *
 *
 * @param size The new font size. This should be a positive integer.
 * @return int64_t Returns 0 if the font size was successfully set, or -1 if an error occurred
 *             (for example, if 'size' is not a valid font size).
 */

int64_t sys_set_font_size(uint64_t size);

/**
 * @brief Draws a pixel on the system screen at a specified position with a specified color.
 *
 * This system call interfaces with the system's hardware to draw a pixel on the screen.
 *
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color A structure representing the RGB color values of the pixel.
 * @return int64_t Returns 0 if the pixel was successfully drawn, or -1 if an error occurred
 *             (for example, if 'x' or 'y' is out of the screen bounds, or 'color' is not a valid color).
 */



/**
 * @brief Clears the system screen to a specified color.
 *
 * This system call interfaces with the system's hardware to clear the screen and set it to a specified color.
 * The color is specified by the 'color' parameter.
 *
 * @param color A structure representing the RGB color values to which the screen should be cleared.
 *              Each color value should be between 0 and 255.
 * @return int64_t Returns 0 if the screen was successfully cleared and set to the specified color, or -1 if an error occurred.

 */

int64_t sys_clear_screen();
//Si estoy aburrido:
/*
int64_t sys_change_background_screen_color(Color color);
int64_t sys_change_font_color(Color color);
int64_t sys_change_error_font_color(Color color);
*/


int64_t sys_draw_pixel(uint64_t x, uint64_t y, Color color);


/*
* @brief Draws a rectangle on the system screen at a specified position with a specified color, width, and height.
*
* This system call interfaces with the system's hardware to draw a rectangle on the screen.
*
* @param x The x-coordinate of the top-left corner of the rectangle.
* @param y The y-coordinate of the top-left corner of the rectangle.
* @param width The width of the rectangle.
* @param height The height of the rectangle.
* @param color A structure representing the RGB color values of the rectangle.
* @return int64_t Returns 0 if the rectangle was successfully drawn, or -1 if an error occurred
*             (for example, if 'x', 'y', 'width', or 'height' is out of the screen bounds, or 'color' is not a valid color).
*/

int64_t sys_draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, Color color);


/**
 * @brief Draws a letter on the system screen at a specified position with a specified color.
 *
 * This system call interfaces with the system's hardware to draw a letter on the screen.
 *
 * @param x The x-coordinate of the top-left corner of the letter.
 * @param y The y-coordinate of the top-left corner of the letter.
 * @param letter The letter to be drawn.
 * @param color A structure representing the RGB color values of the letter.
 * @return int Returns 0 if the letter was successfully drawn, or -1 if an error occurred
 *             (for example, if 'x' or 'y' is out of the screen bounds, 'letter' is not a valid character, or 'color' is not a valid color).
 */

int64_t sys_draw_letter(uint64_t x, uint64_t y, char letter, Color color);



/**
 * @brief Sets the system to a specified mode.
 *
 * @param mode The mode to which the system should be set. This should be either TEXT_MODE or VIDEO_MODE.
 * @return int64_t Returns 0 if the system was successfully set to the specified mode, -1 if an error occurred (for example if the mode is invalid).
 */


int64_t sys_set_mode(uint64_t mode);


/**
 * @brief Gets the dimensions of the system screen.
 *
 * This system call interfaces with the system's hardware to get the dimensions of the screen.
 * The dimensions are written into the 'screen_size' parameter.
 *
 * @param screen_size A pointer to a ScreenSize structure that will be filled with the screen's dimensions.
 * @return int64_t Returns 0 if the dimensions were successfully retrieved, or -1 if an error occurred.
 */


int64_t sys_get_screen_information(ScreenInformation * screen_information);


#endif
/*
Modo texto:
int64_t sys_write(uint64_t fd, const char * buffer, int64_t amount);
int64_t sys_set_font_size(int size);  // este ya hace el resize si entra AL menos 1 caracter !

Modo video:
int64_t sys_draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, Color color);
int64_t sys_draw_letter(uint64_t x, uint64_t y, char letter, Color color);
int64_t sys_draw_pixel(uint64_t x, uint64_t y, Color color);

Ambos modos:
int64_t sys_get_screen_information(ScreenInformation * screen_information);
int64_t sys_set_mode(uint64_t mode)

*/