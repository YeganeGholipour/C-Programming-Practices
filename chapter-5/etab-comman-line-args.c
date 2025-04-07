#include <stdio.h>

#define STOPS 6

void etab(int *tabs, int size, int *position, int spaces) {
    int end = *position + spaces;

    while (*position < end) {
        int is_tab_stop = 0;

        for (int i = 0; i < size; i++) {
            if (*position % tabs[i] == 0) {
                is_tab_stop = 1;
                break;
            }
        }

        if (is_tab_stop && (*position + 1) < end && ((*position + tabs[0]) <= end)) {
            putchar('\t');
            *position += tabs[0]; 
        } else {
            putchar(' ');
            (*position)++;
        }
    }
}



void detab(int *tabs, int size, int *position) {
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
    int tab_stops[argc < 2 ? 1 : argc - 1];
    int size, number;
    int i = 0, c;
    int pos = 0;
    int spaces = 0;

    if (argc < 2) {
        tab_stops[0] = STOPS;
        size = 1;
    } else {
        while (--argc) {
            number = atoi(*++argv);
            tab_stops[i++] = number;
        }
        size = i;
    }

    while ((c = getchar()) != EOF)
    {   
        if (c == ' ') {
            spaces++;
            while ((c = getchar()) == ' ') {
                spaces++;
            }
            etab(tab_stops, size, &pos, spaces);
        }

        else if (c == '\t') {
            detab(tab_stops, size, &pos);
        }
        
        else if (c == '\n') {
            printf("\n");
            pos = 0;
        }
        else {
            putchar(c);
            pos++;
        }
    }
    
    return 0;
}