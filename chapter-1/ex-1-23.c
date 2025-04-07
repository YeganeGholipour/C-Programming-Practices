// A very hard questio


#include <stdio.h>

void remove_comments() {
    int c, next;
    int inside_string = 0, inside_char = 0;

    while ((c = getchar()) != EOF) {
        if (c == '"' && !inside_char) {
            putchar(c);
            inside_string = !inside_string;
        }

        else if (c == '\'' && !inside_string) {
            putchar(c);
            inside_char = !inside_char;
        }

        else if (c == '/' && !inside_char && !inside_string) {
            next = getchar();
            if (next == '/') {
                while ((c = getchar()) != EOF && c != '\n');
                putchar('\n');
            }
            else if (next == '*') {
                while ((c = getchar()) != EOF) {
                    if (c == '*' && (next = getchar()) == '/')
                        break;
                }
            }
            else {
                putchar(c);
                putchar(getchar);
            }
        }
        else {
            putchar(c);
        }

    }
}