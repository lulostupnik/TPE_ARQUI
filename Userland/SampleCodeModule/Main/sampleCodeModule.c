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
    // sys_write(1, "Hello World!\n", 13);
    // put_char('H');
	//All the following code may be removed
    /*uint64_t a=sysWrite(0,0,"hola soy una vaca");
    char string[2]={0,0};
    string[0]=((a%10)+'0');
    sysWrite(0,16,string);*/
    /*
    int x = 0;
    char string[2] = {0,0};
    getFirstKeyStroke();
    while(1){
        string[0] = getFirstKeyStroke();
        if(string[0] != 0){
            if( string[0] >= FIRST_ASCII_CHAR && string[0] <= LAST_ASCII_CHAR){
                sysWrite(x,0,string);
                x+=16;
            }else{
                //special keys handler
            }

        }
    }
    */

    uint64_t c;
    uint64_t x = 0;
    initializeShell();
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;
	return 0xDEADBEEF;
}