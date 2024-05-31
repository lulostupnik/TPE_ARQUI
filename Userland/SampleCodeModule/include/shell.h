#include <libc.h>
#include <eliminator.h>
#include <exceptions.h>
#ifndef CMD_INTERPRETER_H
#define CMD_INTERPRETER_H
#define MAX_COMMAND_SIZE 100
#define MAX_ZOOM 3
#define MIN_ZOOM 1 // en realidad hagamos que sea 2
#define MAX_MODULES 9 // @todo: cambie esto, no se si está bien
//Constants for the shell

#define WELCOME "Bienvenido a hogOS!\n"
#define PROMPT "hogOS>User> "

#define MAX_FONT_SIZE 3
#define MIN_FONT_SIZE 1

//Type Definitions
typedef struct module {
    char *name;
    void (*function)();
} module;


// Function prototypes
int initializeShell();

void interpret();

// Function to zoom in
void zoomIn();

// Function to zoom out
void zoomOut();

void showcurrentTime();

void getRegs();

void clear();


#endif /* CMD_INTERPRETER_H */