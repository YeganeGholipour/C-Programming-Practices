#include <stdio.h>
#include <string.h>

int strindex(char *s, char *t) {
    char *sp = s, *tp = t;
    int len_t = strlen(t);
    int steps;

    while (*sp) {
        if (*sp == *tp) {
            sp++;
            tp++;
            if (*tp == '\0')
                return (sp - s) - len_t;
        } else {
            if (tp != t) {
                steps = tp - t;
                sp = sp - steps + 1;
                tp = t;
            } else {
                sp++;
            }
        }
    }

    return -1;
}
