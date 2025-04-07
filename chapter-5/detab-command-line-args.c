#include <stdio.h>
#include <stdlib.h>

#define STOPS 6  

void detab(int *position, int *tabs, int size) {
    int min_space = tabs[0];
    int spaces;

    for (int i = 1; i < size; i++) {
        spaces = tabs[i] - (*position % tabs[i]); 
        if (spaces < min_space) {
            min_space = spaces;
        }
    }

    for (int i = 0; i < min_space; i++) {
        putchar(' ');  
        (*position)++;  
    }
}

int main(int argc, char *argv[]) {
    int tab_stops[argc > 1 ? argc - 1 : 1];
    int i = 0, c, pos = 0, number;
    int size;

    if (argc == 1) {
        tab_stops[0] = STOPS;
        size = 1;
    } else {
        while (--argc) {
            number = atoi(*++argv);
            if (number <= 0) {
                fprintf(stderr, "Error: Invalid input '%s'. Tab stops must be positive integers.\n", *argv);
                return 1;
            }
            tab_stops[i++] = number;
        }
        size = i;
    }

    while ((c = getchar()) != EOF) {  
        if (c == '\t') {  
            detab(&pos, tab_stops, size);
        } else {
            if (c == '\n') {  
                putchar('\n');
                pos = 0;
            } else {
                putchar(c);  
                pos++;  
            }
        }
    }

    return 0;
}





// int main() {
//     int c, i = 0;  

//     while ((c = getchar()) != EOF) {  
//         if (c == '\t') {  
//             detab(&i);
//         } else {
//             if (c == '\n') {  
//                 printf("\n");
//                 i = 0;
//             } else {
//                 printf("%c", c);  
//                 i++;  
//             }
//         }
//     }

//     return 0;
// }
