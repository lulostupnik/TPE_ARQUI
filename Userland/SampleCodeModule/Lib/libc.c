#include <libc.h>

// Este prototipo va acá?
// static int64_t vfprintf(uint64_t fd, const char *fmt, va_list args);

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



/**
 * @brief Calculates the length of a string.
 *
 * This function calculates the length of the null terminated string pointed to by `str`, excluding the terminating null byte ('\0').
 *
 * @param str The string whose length is to be calculated.
 * @return size_t Returns the number of characters in the string pointed to by `str`.
 */
uint64_t strlen(const char *str) {
    const char *s = str;
    while (*s)
        ++s;
    return s - str;
}



/**
 * @brief Converts a number to a string representation in a specified base.
 *
 * This function converts a number to its string representation in a specified base.
 * It uses a static buffer to hold the result, so the returned string should be used or copied before the next call to `numToString`.
 *
 * @param num The number to be converted.
 * @param base The base to use for the conversion. This should be between 2 and 16 inclusive.
 * @return char* Returns a pointer to the string representation of the number. This string is null-terminated.
 */
char * numToString(uint64_t num, uint64_t base) {
    static char buffer[64];
    char * ptr = &buffer[63];
    *ptr = '\0';
    do {
        *--ptr = "0123456789abcdef"[num % base];
        num /= base;
    } while(num != 0);
    return ptr;
}



/**
 * @brief Writes a string to the standard output.
 *
 * This function uses the sys_write system call to write a string to the standard output (STDOUT).
 * The string is written to the screen. A newline character is appended at the end of the string.
 *
 * @param str The string to write.
 * @return int64_t Returns the number of characters written if the operation was successful, or -1 if an error occurred.
 */
int64_t puts(const char * str) {
    return sys_write(STDOUT, str, strlen(str));
}



/**
 * @brief Writes a character to a file descriptor.
 *
 * This function uses the sys_write system call to write a character to a specified file descriptor.
 *
 * @param c The character to write.
 * @param fd The file descriptor to write to.
 * @return int64_t Returns the 0 if the operation was successful, or -1 if an error occurred.
 */
int64_t fputc(char c, uint64_t fd) {
    return sys_write(fd, &c, 1) == -1 ? -1 : 0;
}



/**
 * @brief Writes formatted output to a specified file descriptor.
 *
 * This auxiliary function is used by printf and fprintf to write formatted output to a specified file descriptor.
 * It takes a variable argument list and a format string, which specifies how subsequent arguments are converted for output.
 *
 * @param fd The file descriptor to write to.
 * @param fmt The format string that specifies how subsequent arguments are converted for output.
 * @param args A variable argument list.
 * @return int64_t Returns the number of characters written if the operation was successful, or -1 if an error occurred.
 */
static int64_t vfprintf(uint64_t fd, const char *fmt, va_list args)
{
    uint64_t flag = 0;
    uint64_t written = 0;

    for (uint64_t i = 0; fmt[i] != '\0'; i++)
    {
        if (fmt[i] == '%' && !flag)
        {
            flag = 1;
            i++;
        }

        if (!flag)
        {
            fputc(fmt[i], fd);
            flag = 0;
            written++;
            continue;
        }

        switch (fmt[i])
        {
            case 'c':
                fputc(va_arg(args, int), fd);
                written++;
                break;
            case 'd':
                written += vfprintf(fd, numToString(va_arg(args, uint64_t), 10), args);
                break;
            case 'x':
                written += vfprintf(fd, "0x", args);
                written += vfprintf(fd, numToString(va_arg(args, uint64_t), 16), args);
                break;
            case 's':
                written += vfprintf(fd, va_arg(args, char *), args);
                break;
            case '%':
                fputc('%', fd);
                written++;
                break;
            default:
                return -1;
        }
    }

    return written;
}



// En está página leimos lo de va_list. Copiamos fprintf y printf e implementamos vfprintf
// http://www.firmcodes.com/write-printf-function-c/
/**
 * @brief Writes formatted output to a specified file descriptor.
 *
 * @param fd The file descriptor to write to.
 * @param fmt The format string that specifies how subsequent arguments are converted for output.
 * @param ... Variable argument list.
 * @return int64_t Returns the number of characters written if the operation was successful, or -1 if an error occurred.
 */
int64_t fprintf(uint64_t fd, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int64_t out = vfprintf(fd, fmt, args);

    va_end(args);
    return out;
}



/**
 * @brief Writes formatted output to the standard output (STDOUT).
 *
 * @param fmt The format string that specifies how subsequent arguments are converted for output.
 * @param ... Variable argument list.
 * @return int64_t Returns the number of characters written if the operation was successful, or -1 if an error occurred.
 */
int64_t printf(const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int64_t out = vfprintf(STDOUT, fmt, args);

    va_end(args);
    return out;
}



/**
 * @brief Reads a specified number of characters from the standard input.
 *
 * This function reads characters from the standard input until it encounters a newline.
 * If it has read the specified number of characters it will cease to write on the buffer unless it encounters a backspace.
 * The characters are stored in a buffer, which is then returned.
 *
 * @param buffer The buffer to store the characters.
 * @param n The maximum number of characters to read. (the last character will be a null terminator)
 * @return char* Returns a pointer to the buffer.
 */
char* gets(char* buffer, int n) {
    int c;
    int i = 0;

    // Read characters until newline, EOF, or maximum number of characters
    while (i < n - 1 && (c = getChar()) != '\n') {
        if (c == '\b' && i > 0) {
            putchar(c);
            i--;
        }
        if (c != '\b' && i < n - 1) {
            putchar(c);
            buffer[i++] = (char)c;
        }
    }

    // Null-terminate the string
    buffer[i] = '\0';

    return buffer;
}



/**
 * @brief Compares two strings.
 *
 * This function compares the two strings str1 and str2. It returns an integer less than, equal to, or greater than zero
 * if str1 is found, respectively, to be less than, to match, or be greater than str2.
 *
 * @param str1 The first string to be compared.
 * @param str2 The second string to be compared.
 * @return int Returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater than str2.
 */
int64_t strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}