#include <stdint.h>
#ifndef TPE_ARQUI_LIBC_H
#define TPE_ARQUI_LIBC_H

#define STDIN 0
#define STDOUT 0
#define STDERR 1 // @TODO esta bien?

/*
 * @TODO En la documentacion del kernel deberia decir que las funciones del KeyDriver devuelven estos valores si no son caracteres ACII.
 */
typedef enum {
    LEFT_CONTROL = 256,         // NOTAR: El valor con el que empieza tiene que ser mas grande al ultimo de la tabla ASCII
    LEFT_SHIFT,
    RIGHT_SHIFT,
    KEYPAD_STAR_PRTSC,
    LEFT_ALT,
    CAPS_LOCK,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    NUM_LOCK,
    SCROLL_LOCK,
    HOME_KEYPAD,
    UP_ARROW_KEYPAD,
    PG_UP_KEYPAD,
    LEFT_ARROW_KEYPAD,
    RIGHT_ARROW_KEYPAD,
    PLUS_KEYPAD,
    END_KEYPAD,
    DOWN_ARROW_KEYPAD,
    PG_DN_KEYPAD,
    INS_KEYPAD,
    DEL_KEYPAD,
    SYS_REQ_AT,
    NONE1, // no hay tecla de scanCode 0x55
    NONE2, // no hay tecla de scan code 0x56
    F11,
    F12
} specialCodes;



/**
 * Structure representing all the registers
 */
typedef struct registers{
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;
} RegisterSet;



/**
 * @brief Reads a character from the standard input.
 *
 * This function uses the read system call to read a character from the standard input (STDIN) (the keyboard buffer)
 * It blocks until a character is available.
 *
 * @return int64_t Returns the value of the read character.
 */
int64_t getChar();



/**
 * @brief Writes a character to the standard output.
 *
 * This function uses the write system call to write a character to the standard output (STDOUT) (the screen)
 *
 * @param c The character to write.
 */
int64_t putChar(char c);



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
int64_t beep(uint64_t frequency, uint64_t duration);



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
int64_t getRegisters(RegisterSet *registers);



/**
 * @brief Clears the system screen.
 *
 * This function uses the sys_clear_screen system call to clear the system screen.
 * The screen is cleared to black.
 *
 * @return int64_t Returns 0 if the screen was successfully cleared, or -1 if an error occurred.
 */
int64_t clearScreen();



/**
 * @brief Sets the font size of the system console.
 *
 * This function uses the sys_set_font_size system call to set the font size of the system console.
 * The font size is set to the specified size.
 *
 * @param size The desired font size.
 * @return int64_t Returns 0 if the font size was successfully set, or -1 if an error occurred.
 */
int64_t setFontSize(uint64_t size);




#endif //TPE_ARQUI_LIBC_H
