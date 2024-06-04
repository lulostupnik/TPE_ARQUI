#include <shell.h>


static void help();

static uint64_t printedChars = 0;
static uint64_t font_size = 1; // font_size 1 is the default size

static void toUtcMinus3(time_struct * time);

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
    fprintf(STDERR, "Invalid Command! Try Again >:(\n");
    // puts("Invalid Command! Try Again >:(\n"); // @todo: esto se imprime siempre
    //opCode_exception();
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
    time_struct time;
    sys_get_time(&time);
    toUtcMinus3(&time);
    printf("%d/%d/%d [d/m/y]\n", time.day, time.month, time.year);
    int64_t h = time.hour;
    printf("%d:%d:%d [hour/min/sec] (Argentina)\n", h, time.minutes, time.seconds);  // la hora es -3 para que este en tiempo argentino.
    return;
}


static void toUtcMinus3(time_struct * time) {
    int8_t new_time_hour = (time->hour - 3);
    // time->hour = (time->hour - 3);
    if (time->hour < 0) {
        // time->hour += 24;
        new_time_hour += 24;
        time->day--;
        if (time->day == 0) { // podría ser <= pero nunca se va a dar
            time->month--;
            if (time->month == 0) {
                time->month = 12;
                time->year--;
            }
            if(time->month == 2){
                time->day = 28;
                if(time->year % 4 == 0){
                    time->day = 29;
                }
            } else if(time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11){
                time->day = 30;
            } else {
                time->day = 31;
            }
        }
    }
    time->hour = new_time_hour;
}



void getRegs(){
    print_register_snapshot();
    return;
}

void clear() {
    // puts("Clearing screen...\n");
    clear_screen();
    // puts("Screen cleared!\n");
}




/*
void toUtc3(time_struct * time){
    time->hour = (time->hour + 3);
    if(time->hour >= 24){
        time->hour -= 24;
        time->day++;
        uint64_t max_days;
        if(time->month == 2){
            max_days = 28;
            if(time->year % 4 == 0){
                max_days = 29;
            }
        } else if(time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11){
            max_days = 30;
        } else {
            max_days = 31;
        }
        if(time->day > max_days){ // && (time->month == 4 || time->month == 6 || time->month == 9 || time->month == 11)
            time->day = 1; // -= max_days
            time->month++;
            if(time->month > 12){
                time->month = 1;
                time->year++;
            }
        }
    }
}
 */