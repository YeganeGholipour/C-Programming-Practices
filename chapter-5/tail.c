#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER 10
#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int tail(char *line_pointer[], int max_lines, int line_nums);
int readline(char *line_pointer[], int max_lines);
int my_getline(char *line, int max_len);
void writelines(char *line_pointer[], int size, int line_nums);
char *alloc(int len);
int process_args(int argc, char *argv[]);

int readline(char *lineptr[], int max_lines) {
    char line[MAXLEN];
    int length, nlines = 0;
    char *p;

    while ((length = my_getline(line, MAXLEN)) > 0) {
        if ((nlines < max_lines) && ((p = alloc(length)) != NULL)) {
            line[length - 1] = '\0'; 
            strcpy(p, line);
            lineptr[nlines++] = p;
        } else {
            fprintf(stderr, "Error: Not enough space to allocate memory!\n");
            return -1;
        }
    }
    return nlines;
}

int my_getline(char *line, int max_len) {
    int c, i = 0;
    while (i < max_len - 1 && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

void writelines(char *lineptr[], int size, int number) {
    if (number > size) {
        fprintf(stderr, "Error: requested more lines than available\n");
        number = size;
    }

    char **p = lineptr + (size - number);
    while (number-- > 0) {
        printf("%s\n", *p++);
    }
}

char *alloc(int len) {
    char *p = malloc(len + 1); 
    if (!p) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    return p;
}

int process_args(int argc, char *argv[]) {
    int n = NUMBER; 
    if (argc == 3 && strcmp(argv[1], "-n") == 0) {
        n = atoi(argv[2]);
    }
    return n;
}

int tail(char *line_pointer[], int max_line, int line_nums) {
    int nlines = 0;
    if ((nlines = readline(line_pointer, max_line)) > 0) {
        writelines(line_pointer, nlines, line_nums);

        for (int i = 0; i < nlines; i++) {
            free(line_pointer[i]);
        }

        return 0;
    } else {
        fprintf(stderr, "Error: Input is too big to process!\n");
        return 1;
    }
}

int main(int argc, char *argv[]) {
    int n = process_args(argc, argv);
    return tail(lineptr, MAXLINES, n);
}
