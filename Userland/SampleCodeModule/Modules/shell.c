#include <shell.h>

static void help();

static uint64_t printedChars = 0;
static uint64_t font_size = 1; // font_size 1 is the default size

static module modules[] = {
    {"help", help},
    {"time", showcurrentTime},
    {"eliminator", eliminator},
    {"zoomin", zoomIn},
    {"zoomout", zoomOut},
    {"getregs", getRegs},
    {"dividebyzero", div0},
    {"opcode", op_code},
    {"clear", clear}
};


int initializeShell(){

    setFontSize(font_size);
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
    for(int i = 0; i < MAX_MODULES; i++){
        if(strcmp(shellBuffer,modules[i].name)==0){
            modules[i].function();
            return;
        }
    }
    //@TODO: Agregar excepciones para comandos no encontrados
    puts("Invalid Command! Try Again >:(\n"); // @todo: esto se imprime siempre
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
    puts("clear: Clears the screen.\n");
}



// Function to zoom in
void zoomIn(){
    if(font_size < MAX_FONT_SIZE){
        font_size++;
        setFontSize(font_size);
        // puts("Zooming in...\n");
    } else {
        puts("Maximum font size reached!\n");
    }
    return;
}

// Function to zoom out
void zoomOut(){
    if(font_size > MIN_FONT_SIZE){
        font_size--;
        setFontSize(font_size);
    } else {
        puts("Minimum font size reached!\n");
    }
    return;
}

void showcurrentTime(){
    puts("Current time: ");
    return;
}

void getRegs(){
    print_register_snapshot();
    return;
}

void clear() {
    puts("Clearing screen...\n");
    clearScreen();
    puts("Screen cleared!\n");
}

