#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

int cmp_str(void **a, void **b);
int cmp_num(void **a, void **b);
int strcasecmp(const char *s1, const char *s2);
void extract_string(char *s, char *string);
void get_field(void *base[], char *splitted_lines[], int col_num, int nlines);
void quicksort(void *base[], int low, int high, int (*compar)(void **, void **));
int partition(void **base, int low, int high, int (*compar)(void **, void **));
void swap(void **a, void **b);
int readline(char **base, int max_lines);
int my_getline(char *line, int max_len);
void writeline(void **base, int len);
char *alloc(int len);
void afree(void **base, int len);

char *lineptr[MAXLINES];
int int_flag;
int reverse_flag;
int fold_flag;
int dir_flag;
int field;

int main(int argc, char *argv[]) {
    int nlines;
    char *splited_lines[MAXLINES];
    if ((nlines = readline(lineptr, MAXLINES)) > 0) {
        for (int i = 1; i < argc; i++) {
            int_flag = 0;
            reverse_flag = 0;
            fold_flag = 0;
            dir_flag = 0;
            field = 0;
            for (int j = 1; j < strlen(argv[i]); j++) {
                char element = argv[i][j];
    
                switch (element)
                {
                case 'n':
                    int_flag = 1;
                    printf("Numeric sort enabled (-n)\n");
                    fflush(stdout);
                    break;
    
                case 'r':
                    reverse_flag = 1;
                    printf("Reverse order enabled (-r)\n");
                    fflush(stdout);
                    break;
                
                case 'f':
                    fold_flag = 1;
                    printf("fold order enabled (-f)\n");
                    fflush(stdout);
                    break;
                
                case 'd':
                    dir_flag = 1;
                    printf("directory order enabled (-d)\n");
                    fflush(stdout);
                    break;
                
                default:
                    if (isdigit(element)) {
                        field = element - '0'; 
                    }
                    break;
                }
            }
            
            if (field != 0) {
                printf("Run for field: %d\n", field);
                get_field((void **)lineptr, splited_lines, field-1, nlines);
                quicksort((void **)splited_lines, 0, nlines - 1, (int_flag ? cmp_num : cmp_str));
                writeline((void **)splited_lines, nlines);
                afree((void **)splited_lines, nlines);
            } else {
                quicksort((void **)lineptr, 0, nlines - 1, (int_flag ? cmp_num : cmp_str));
                writeline((void **)lineptr, nlines);
            }
        }

        afree((void **)lineptr, nlines);
        return 0;

    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}


int cmp_num(void **a, void **b) {
    double num1 = atof(*(char **)a);
    double num2 = atof(*(char **)b);

    if (reverse_flag) {
        if (num1 < num2) return 1;  
        if (num1 > num2) return -1;
    } else {
        if (num1 < num2) return -1;
        if (num1 > num2) return 1;
    }

    return 0;
}


int cmp_str(void **a, void **b) {
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;

    char string1[MAXLEN];
    char string2[MAXLEN];
    
    if (dir_flag) {
        extract_string(s1, string1);  
        extract_string(s2, string2);  

        s1 = string1; 
        s2 = string2;
    }

    if (fold_flag) {
        return strcasecmp(s1, s2);
    }

    return strcmp(s1, s2);  
}


int strcasecmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

void extract_string(char *s, char *string) {
    while (*s) {
        if (isalnum((unsigned char)*s) || isblank((unsigned char)*s)) {
            *string++ = *s;
        }
        s++;
    }

    *string = '\0';  
}

void get_field(void *base[], char *splitted_lines[], int col_num, int nlines) {
    char buffer[MAXLEN];
    char *p;

    for (int i = 0; i < nlines; i++) {
        char *element = (char *)base[i];
        int count = 0;
        int len = 0;

        // Reset buffer before starting each new line
        memset(buffer, 0, MAXLEN);

        while (*element != '\0') {
            // printf("element: %s\n", element);
            if (count == col_num) {
                while (*element != '\0' && *element != '\t' && *element != '\n') {
                    if (len < MAXLEN - 1) {  
                        buffer[len++] = *element;
                    }
                    element++;
                }
                break;
            }
            else if (*element == '\t') {
                count++;
            }
            else {
                element++;
            }
        }

        buffer[len] = '\0';
        printf("the part of column %d: %s\n", col_num + 1, buffer);

        p = alloc(len + 1);
        strcpy(p, buffer);
        splitted_lines[i] = p;
    }
}



void quicksort(void *base[], int low, int high, int (*compar)(void **, void **)) {
    if (low < high) {
        int p = partition(base, low, high, compar);
        quicksort(base, low, p, compar);
        quicksort(base, p + 1, high, compar);
    }
}

int partition(void **base, int low, int high, int (*compar)(void **, void **)) {
    void **pivot = base + low;
    int left = low - 1;
    int right = high + 1;

    while (1) {
        do {
            right--;
        } while (compar(base + right, pivot) > 0);

        do {
            left++;
        } while (compar(base + left, pivot) < 0);

        if (left >= right)
            return right;

        swap(base + left, base + right);
    }
}

void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

int readline(char *lineptr[], int max_lines) {
    int nlines = 0;
    char line[MAXLEN];
    int len;
    char *p;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines < max_lines && (p = alloc(len)) != NULL) {
            line[len - 1] = '\0';  
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

int my_getline(char *line, int max_len) {
    int c, i = 0;
    while (i < max_len - 1 && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }

    if (c == '\n')
        line[i++] = '\n';

    line[i] = '\0';
    return i;
}

void writeline(void **base, int len) {
    for (int i = 0; i < len; i++) 
        printf("%s\n", ((char **)base)[i]);
}

void afree(void **base, int len) {
    for (int i = 0; i < len; i++) {
        if (base[i] != NULL)
            free(base[i]);
    }
}

char *alloc(int len) {
    char *ptr = malloc(len);
    if (ptr == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    return ptr;
}
