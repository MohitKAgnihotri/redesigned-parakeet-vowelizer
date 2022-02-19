#include <stdio.h>
#include "user_interface.h"


void get_line_from_stdin(char *line, int max_length)
{
    int i = 0;
    char c;
    while (i < max_length - 1 && (c = getchar()) != '\n')
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
}