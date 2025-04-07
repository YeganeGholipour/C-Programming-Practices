#include <stdio.h>

int main () {
    int t = 0, b = 0, n = 0, c;  
    while ((c = getchar()) != EOF) {
        if (c == '\n')          
            n++;
        else if (c == '\t')     
            t++;
        else if (c == '\b')     
            b++;
    }

    printf("New Lines: %d\nBlanks: %d\nTabs: %d\n", n, b, t);
    return 0;
}
