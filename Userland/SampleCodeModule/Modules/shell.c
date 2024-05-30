#include <shell.h>

static void help();

static uint64_t printedChars = 0;

static module modules[] = {
    {"help", help},
    {"time", showcurrentTime},
    {"eliminator", eliminator},
    {"zoomin", zoomIn},
    {"zoomout", zoomOut},
    {"getregs", getRegs},
    {"dividebyzero", div0},
    {"opcode", op_code}
};


int initializeShell(){
    puts(WELCOME);
    help();
    while (1){
        interpret();
    }
    
}
void interpret(){
    puts(PROMPT);
    char shellBuffer[MAX_COMMAND_SIZE];
    gets(shellBuffer, MAX_COMMAND_SIZE); // @todo: es -1 ?
    if(strlen(shellBuffer)==0){
        return;
    }
    for(int i=0;i<MAX_MODULES;i++){
        if(strcmp(shellBuffer,modules[i].name)==0){
            modules[i].function();
            break;
        }
    }
    //@TODO: Agregar excepciones para comandos no encontrados
    puts("Invalid Command! Try Again >:(\n");
    //opCode_exception();
}

static void help(){
    puts("Comandos disponibles:\n");
    puts("help: Muestra todos los modulos disponibles del sistema operativo.\n");
    puts("time: Muestra la hora actual del sistema.\n");
    puts("eliminator: Inicia el juego Eliminator, un clasico.\n");
    puts("zoomin: Agranda los caracteres en pantalla.\n");
    puts("zoomout: Achica  la pantalla.\n");
    puts("getregs: Muestra el estado actual de los registros.\n");
    puts("div0: Genera una excepcion de division por cero.\n");
    puts("opcode: Genera una excepcion de codigo de operacion invalido.\n");
}



// Function to zoom in
void zoomIn(){
    // puts("Zooming in...\n");
    return;
}

// Function to zoom out
void zoomOut(){
    // puts("Zooming out...\n");
    return;
}

void showcurrentTime(){
    // puts("Current time: ");
    return;
}

void getRegs(){
    // puts("Current registers: ");
    return;
}