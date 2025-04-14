#include <stdio.h>
#include <ctype.h>
#include "readline.h"

int read_line(char str[], int n) {
    int ch, i = 0;

    while ((ch = getchar()) != EOF && isspace(ch))
    ;

    if (ch == EOF)
        return 0; // or -1, or handle as you like

    do {
        if (i < n)
            str[i++] = ch;
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    str[i] = '\0';
    return i;
}