#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
    int c, w, state;
    w = 0;  
    state = OUT;  

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;  
        else if (state == OUT) {
            state = IN; 
            w++;  
    }
}
printf("Word count: %d\n", w); 
}
