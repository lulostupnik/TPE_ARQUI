#include <strings.h>

int char_in_string(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
        {
            return 1;
        }
    }
    return 0;
}