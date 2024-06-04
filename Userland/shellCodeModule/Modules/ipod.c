#include <ipod.h>

/*
static Song * my_songs[SONG_AMOUNT];

Note happy_birthday_notes[] = {
        {262, 500}, // C4, quarter note
        {262, 500}, // C4, quarter note
        {294, 500}, // D4, quarter note
        {262, 500}, // C4, quarter note
        {349, 500}, // F4, quarter note
        {330, 500}, // E4, quarter note
};

Song happy_birthday = {
        .note_count = 6,
        .notes = happy_birthday_notes,
        .name = "Happy Birthday"
};
 */

/*
void initialize_songs() {
    my_songs[0] = &happy_birthday;
    // Initialize other songs here...
}
*/


void ipod_menu(){
    initialize_songs();
    puts("Which of the following songs would you like to hear:\n");
    for(char i = 0; i < SONG_AMOUNT; i++){
        printf("%c. %s\n", i + '0', my_songs[i]->name);
    }

    uint64_t song_number;
    song_number = (uint64_t) (getChar() - '0');
    if(song_number >= SONG_AMOUNT){
        fprintf(STDERR, "Invalid song id\n");
        // puts("Invalid song number\n");
        return;
    }
    play_song(my_songs[song_number]);

    // se interpreta lo obtenido viendo si existe la cancion
    // si existe se reproduce
}

void play_song(Song* song) {
    for (int i = 0; i < song->note_count; i++) {
        Note note = song->notes[i];
        sys_beep(note.frequency, note.duration / MS_PER_TICK );
    }
}


