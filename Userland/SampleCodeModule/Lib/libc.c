#include <libc.h>
#include <stdint.h>
#include <syscallFunctions.h>



/**
 * @brief Reads a character from the standard input.
 *
 * This function uses the read system call to read a character from the standard input (STDIN) (the keyboard buffer)
 * It blocks until a character is available.
 *
 * @return int64_t Returns the value of the read character.
 */
int64_t getChar(){
    char c;
    while( sys_read(STDIN, &c, 1) == 0 );
    return c;
}



/**
 * @brief Writes a character to the standard output.
 *
 * This function uses the sys_write system call to write a character to the standard output (STDOUT)
 * (The character is written to the screen)
 *
 * @param c The character to write.
 */
void putChar(char c) {
    sys_write(STDOUT, &c, 1);
}



/**
 * @brief Generates a beep sound.
 *
 * This function uses the sys_beep system call to generate a beep sound.
 * The beep sound is produced by the system speaker.
 *
 * @param frequency The frequency of the beep sound in hertz.
 * @param duration The duration of the beep sound in milliseconds.
 * @return int64_t Returns 0 if the beep was successfully generated, or -1 if an error occurred.
 */
int64_t beep(uint64_t frequency, uint64_t duration) {
    return sys_beep(frequency, duration);
}



/**
 * @brief Retrieves the saved state of the registers. Use keys XXXX to create snapshot. Only last snapshot will be shown
 *
 * This function uses the sys_get_register_snapshot system call to retrieve the saved state of the registers.
 * If the registers have been previously saved, this function writes the saved state into the provided RegisterSet structure.
 * If no registers have been saved, the function does not modify the provided structure.
 *
 * @param registers Pointer to a RegisterSet structure where the saved state of the registers will be written.
 * @return int64_t Returns 1 if the registers were previously saved and their state has been written into the provided structure.
 *                 Returns 0 if no registers have been saved, in which case the provided structure is not modified.
 */
int64_t getRegisters(RegisterSet *registers) {
    return sys_get_register_snapshot(registers);
}



/**
 * @brief Clears the system screen.
 *
 * This function uses the sys_clear_screen system call to clear the system screen.
 * The screen is cleared to black.
 *
 * @return int64_t Returns 0 if the screen was successfully cleared, or -1 if an error occurred.
 */
int64_t clearScreen() {
    return sys_clear_screen();
}



/**
 * @brief Sets the font size of the system console.
 *
 * This function uses the sys_set_font_size system call to set the font size of the system console.
 * The font size is set to the specified size.
 *
 * @param size The desired font size.
 * @return int64_t Returns 0 if the font size was successfully set, or -1 if an error occurred.
 */
int64_t setFontSize(uint64_t size) {
    return sys_set_font_size(size);
}


