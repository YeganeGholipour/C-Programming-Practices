#include <stdio.h>

int main() {
    int i, c;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            i ++;
    }
    printf("Count: %d\n", i);
}