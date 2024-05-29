#include <libc.h>
#include <eliminator.h>
#include <regs.h>
#include <fontsize.h>
#include <systemtime.h>
#include <exceptions.h>
#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H
#define MAX_COMMAND_SIZE 100
#define MAX_ZOOM 4
#define MIN_ZOOM 1 // en realidad hagamos que sea 2
#define MAX_MODULES 6
//Constants for the shell

#define WELCOME "Bienvenido a hogOS!"
#define PROMPT "hogOS>User> "

//Type Definitions
typedef struct module {
    char *name;
    void (*function)();
} module;


// Function prototypes

int initializeShell();
void interpret();

#endif /* CMD_INTERPRETER_H */