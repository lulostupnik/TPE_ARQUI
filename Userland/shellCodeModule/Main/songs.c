#include "ipod.h"

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

Song* my_songs[SONG_AMOUNT] = {
        &happy_birthday
        // Initialize other songs here...
};

void initialize_songs() {
    my_songs[0] = &happy_birthday;
    // Initialize other songs here...
}