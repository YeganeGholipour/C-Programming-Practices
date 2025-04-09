#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

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

int main(int argc, char *argv[]) {
    int int_flag = 0;
    int reverse_flag = 0;
    int nlines;
    char *lineptr[MAXLINES];

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            int_flag = 1;
            printf("Numeric sort enabled (-n)\n");
            fflush(stdout);
        } else if (strcmp(argv[i], "-r") == 0) {
            reverse_flag = 1;
            printf("Reverse order enabled (-r)\n");
            fflush(stdout);
        }
    }

    printf("reverse: %d, int_flag: %d\n", reverse_flag, int_flag);
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

int cmp_str(void **a, void **b) {
    return strcmp(*(char **)a, *(char **)b);
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
