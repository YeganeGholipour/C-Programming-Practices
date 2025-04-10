#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

void parse_flags(int argc, char **argv, int *int_flag, int *reverse_flag, int *fold_flag, int *dir_flag);
int cmp_str(void **a, void **b);
int cmp_num(void **a, void **b);
void quicksort(void *base[], int low, int high, int (*compar)(void **, void **));
int partition(void **base, int low, int high, int (*compar)(void **, void **));
void swap(void **a, void **b);
int readline(char **base, int max_lines);
int my_getline(char *line, int max_len);
void writeline(void **base, int len, void (*sort)(void **, int));
char *alloc(int len);
void afree(void **base, int len);
void descending(void **base, int len);
void ascending(void **base, int len);
void reverse(void **base, int len);

int fold_flag = 0;
int dir_flag = 0;

int main(int argc, char *argv[]) {
    int int_flag = 0;
    int reverse_flag = 0;
    int nlines;
    char *lineptr[MAXLINES];

    parse_flags(argc, argv, &int_flag, &reverse_flag, &fold_flag, &dir_flag);
    printf("reverse: %d, int_flag: %d, fold_flag: %d, dir_flag: %d\n", reverse_flag, int_flag, fold_flag, dir_flag);
    fflush(stdout);

    if ((nlines = readline(lineptr, MAXLINES)) > 0) {
        quicksort((void **)lineptr, 0, nlines - 1, (int_flag ? cmp_num : cmp_str));
        writeline((void **)lineptr, nlines, (reverse_flag ? descending : ascending));
        afree((void **)lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

void parse_flags(int argc, char **argv, int *int_flag, int *reverse_flag, int *fold_flag, int *dir_flag) {
    for (int i = 1; i < argc; i++)
        for (int j = 1; j < strlen(argv[i]); j++) {
            char element = argv[i][j];
            if (element == 'n') {
                *int_flag = 1;
                printf("Numeric sort enabled (-n)\n");
                fflush(stdout);
            } else if (element == 'r') {
                *reverse_flag = 1;
                printf("Reverse order enabled (-r)\n");
                fflush(stdout);
            } else if (element == 'f') {
                *fold_flag = 1;
                printf("fold order enabled (-f)\n");
                fflush(stdout);
            } else if (element == 'd') {
                *dir_flag = 1;
                printf("directory order enabled (-d)\n");
                fflush(stdout);
            }
        }
}

void reverse(void **base, int len) {
    int i = 0;
    int j = len - 1;

    while (i < j) {
        swap(&base[i], &base[j]);
        i++;
        j--;
    }
}

void descending(void **base, int len) {
    reverse(base, len); 
    for (int i = 0; i < len; i++) 
        printf("%s\n", ((char **)base)[i]);
}

void ascending(void **base, int len) {
    for (int i = 0; i < len; i++) 
        printf("%s\n", ((char **)base)[i]);
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

int cmp_num(void **a, void **b) {
    double num1 = atof(*(char **)a);
    double num2 = atof(*(char **)b);

    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
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

void writeline(void **base, int len, void (*sort)(void **, int len)) {
    sort(base, len);
}

void afree(void **base, int len) {
    for (int i = 0; i < len; i++) {
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
