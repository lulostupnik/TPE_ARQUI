#include "ipod.h"

Note happy_birthday_notes[] = {
        {262, 500}, // C4, quarter note
        {262, 500}, // C4, quarter note
        {294, 500}, // D4, quarter note
        {262, 500}, // C4, quarter note
        {349, 500}, // F4, quarter note
        {330, 500}, // E4, quarter note
        {262, 500}, // C4, quarter note
        {262, 500}, // C4, quarter note
        {294, 500}, // D4, quarter note
        {262, 500}, // C4, quarter note
        {392, 500}, // G4, quarter note
        {349, 500}, // F4, quarter note
        {262, 500}, // C4, quarter note
        {262, 500}, // C4, quarter note
        {523, 500}, // C5, quarter note
        {392, 500}, // G4, quarter note
        {349, 500}, // F4, quarter note
        {330, 500}, // E4, quarter note
        {294, 500}, // D4, quarter note
        {494, 500}, // B4, quarter note
        {494, 500}, // B4, quarter note
        {440, 500}, // A4, quarter note
        {349, 500}, // F4, quarter note
        {392, 500}, // G4, quarter note
        {349, 500}, // F4, quarter note
};

Note arcade_song_notes[] = {
        {262, 250}, // C4, eighth note
        {330, 250}, // E4, eighth note
        {392, 250}, // G4, eighth note
        {523, 250}, // C5, eighth note
        {392, 250}, // G4, eighth note
        {330, 250}, // E4, eighth note
        {262, 250}, // C4, eighth note
        {294, 250}, // D4, eighth note
        {349, 250}, // F4, eighth note
        {440, 250}, // A4, eighth note
        {294, 250}, // D4, eighth note
        {440, 250}, // A4, eighth note
        {349, 250}, // F4, eighth note
        {294, 250}, // D4, eighth note
        {262, 250}, // C4, eighth note
        {330, 250}, // E4, eighth note
        {392, 250}, // G4, eighth note
        {523, 250}, // C5, eighth note
        {392, 250}, // G4, eighth note
        {330, 250}, // E4, eighth note
        {262, 250}, // C4, eighth note
};



Song happy_birthday = {
        .note_count = 25,
        .notes = happy_birthday_notes,
        .name = "Happy Birthday"
};

Song arcade_song = {
        .note_count = 21,
        .notes = arcade_song_notes,
        .name = "Arcade Song"
};

Song* my_songs[SONG_AMOUNT] = {
        &happy_birthday,
        &arcade_song
};

/*
void initialize_songs() {
    my_songs[0] = &happy_birthday;
    // Initialize other songs here...
}
*/

/*
void play_song() {
    // Frequencies for the notes in the song.
    uint32_t C4 = 262;
    uint32_t D4 = 294;
    uint32_t E4 = 330;
    uint32_t F4 = 349;
    uint32_t G4 = 392;
    uint32_t A4 = 440;
    uint32_t B4 = 494;
    uint32_t C5 = 523;

    // Duration of each note in milliseconds.
    int quarter_note = 500;
    int half_note = quarter_note * 2;

    // Play the song.
    beep(C4, quarter_note);
    beep(C4, quarter_note);
    beep(G4, quarter_note);
    beep(G4, quarter_note);
    beep(A4, quarter_note);
    beep(A4, quarter_note);
    beep(G4, half_note);

    beep(F4, quarter_note);
    beep(F4, quarter_note);
    beep(E4, quarter_note);
    beep(E4, quarter_note);
    beep(D4, quarter_note);
    beep(D4, quarter_note);
    beep(C4, half_note);
}
 */

/*
void play_song() {
    // Frequencies for the notes in the song.
    uint32_t C4 = 262;
    uint32_t D4 = 294;
    uint32_t E4 = 330;
    uint32_t F4 = 349;
    uint32_t G4 = 392;
    uint32_t A4 = 440;
    uint32_t B4 = 494;
    uint32_t C5 = 523;

    // Duration of each note in milliseconds.
    int quarter_note = 500;
    int eighth_note = quarter_note / 2;
    int half_note = quarter_note * 2;

    // Play the song.
    sys_beep(C4, quarter_note);
    sys_beep(C4, quarter_note);
    sys_beep(D4, quarter_note);
    sys_beep(C4, quarter_note);
    sys_beep(F4, quarter_note);
    sys_beep(E4, quarter_note);

    sys_beep(C4, quarter_note);
    sys_beep(C4, quarter_note);
    sys_beep(D4, quarter_note);
    sys_beep(C4, quarter_note);
    sys_beep(G4, quarter_note);
    sys_beep(F4, quarter_note);

    sys_beep(C4, quarter_note);
    sys_beep(C4, quarter_note);
    sys_beep(C5, quarter_note);
    sys_beep(A4, quarter_note);
    sys_beep(F4, quarter_note);
    sys_beep(E4, quarter_note);
    sys_beep(D4, quarter_note);

    sys_beep(B4, quarter_note);
    sys_beep(B4, quarter_note);
    sys_beep(A4, quarter_note);
    sys_beep(F4, quarter_note);
    sys_beep(G4, quarter_note);
    sys_beep(F4, quarter_note);
}
 */