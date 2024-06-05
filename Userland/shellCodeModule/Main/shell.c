#include <shell.h>


static void help();


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
    {"clear", clear},
    {"ipod", ipod_menu}
};



int main(){
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
    gets(shellBuffer, MAX_COMMAND_SIZE);
    if(strlen(shellBuffer)==0){
        return;
    }
    for(int i = 0; i < MAX_MODULES; i++){
        if(strcmp(shellBuffer,modules[i].name)==0){
            modules[i].function();
            return;
        }
    }
    fprintf(STDERR, "Invalid Command! Try Again >:(\n");

}

static void help(){

    puts("\nComandos disponibles:\n\n");
    puts("- help: Muestra todos los modulos disponibles del sistema operativo.\n");
    puts("- time: Muestra la hora actual del sistema.\n");
    puts("- eliminator: Inicia el juego Eliminator, un clasico.\n");
    puts("- zoomin: Agranda los caracteres en pantalla.\n");
    puts("- zoomout: Achica  la pantalla.\n");
    puts("- getregs: Muestra el estado actual de los registros.\n");
    puts("- dividebyzero: Genera una excepcion de division por cero.\n");
    puts("- opcode: Genera una excepcion de codigo de operacion invalido.\n");
    puts("- clear: Limpia la pantalla.\n");
    puts("- ipod: Inicia el reproductor de musica.\n\n");

}



// Function to zoom in
void zoomIn(){
    if(font_size < MAX_FONT_SIZE){
        font_size++;
        setFontSize(font_size);
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
    time_struct time;
    sys_get_time(&time);
    printf("%d/%d/%d [d/m/y]\n", time.day, time.month, time.year);
    int64_t h = time.hour;
    printf("%d:%d:%d [hour/min/sec] (UTC)\n", h, time.minutes, time.seconds);  // la hora es -3 para que este en tiempo argentino.
    return;
}



void getRegs(){
    print_register_snapshot();
    return;
}

void clear() {
    clear_screen();
}

