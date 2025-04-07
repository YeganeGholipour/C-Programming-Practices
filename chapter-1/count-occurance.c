#include <stdio.h>

int main() {
    int c, white, other, i;
    char digit[10];

    for (i=0; i<10; i++)
        digit[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t')
            white++;
        else if (c >= '0' && c <= '9')
            digit[c-'0']++;
        else
            other++;
    }

    printf("digits= \n");
    for (i=0; i<10; i++)
        printf("%d: %d\n", i, digit[i]);
    printf("white spaces = %d\n other = %d\n", white, other);

}