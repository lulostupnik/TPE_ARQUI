/* sampleCodeModule.c */
#include <syscallFunctions.h>
#include <libc.h>
#include <shell.h>
char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


#define FIRST_ASCII_CHAR 32
#define LAST_ASCII_CHAR 126
int main() {

    uint64_t c;
    uint64_t x = 0;
    initializeShell();
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	return 0xDEADBEEF;
}