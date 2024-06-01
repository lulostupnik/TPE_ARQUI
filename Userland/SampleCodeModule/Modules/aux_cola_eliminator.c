/*
int char_in_string(char c, char * str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            return 1;
        }
    }
    return 0;
}


int get_wanted(char * in, int in_len, char * wanted, char * out) {
    int count = 0;
    for (int i = 0; i < in_len; i++) {
        if (char_in_string(in[i], wanted)) {
            out[count] = in[i];
            count++;
        }
    }
    out[count] = '\0';
    return count;
}
*/