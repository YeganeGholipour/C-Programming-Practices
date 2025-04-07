#include <stdio.h>

int main() {
    int c, prev = 0;

    while ((c=getchar()) != EOF) {
        if (c == ' ' && prev == ' ')
            ;
        else
            putchar(c);
        prev = c;
    }
}