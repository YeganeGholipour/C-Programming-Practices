#include <stdio.h>

#define TAB_STOP 4  

int detab(int position) {
    return TAB_STOP - (position % TAB_STOP);
}

int main() {
    int c, spaces, i;
    int curr_pos = 0; 

    while ((c = getchar()) != EOF) {
        if (c == '\t') {  
            spaces = detab(curr_pos);
            for (i = 0; i < spaces; i++) {
                putchar(' ');
                curr_pos++;  
            }
        } 
        else {
            putchar(c);
            curr_pos++;

            if (c == '\n')  
                curr_pos = 0;
        }
    }
    return 0;
}
