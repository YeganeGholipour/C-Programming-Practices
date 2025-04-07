#include <stdio.h>

int main() {
    int c, length = 0, i;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (length > 0) {  
                for (i = 0; i < length; i++) {
                    putchar('-');
                }
                putchar('\n');  
                length = 0;     
            }
        } else {
            length++;  
        }
    }

    return 0;
}
