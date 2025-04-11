#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXTOKEN 1000

void parse_flags(int argc, char **argv, int *int_flag, int *reverse_flag, int *fold_flag, int *dir_flag, int *fields, int *field_count);
int cmp_str(void **a, void **b, int int_flag, int reverse_flag, int fold_flag, int dir_flag);
int cmp_num(void **a, void **b, int int_flag, int reverse_flag, int fold_flag, int dir_flag);
void quicksort(void *base[], void *buffer[], int low, int high, int (*compar)(void **, void **, int, int, int, int), int int_flag, int reverse_flag, int fold_flag, int dir_flag);
int partition(void **base, void **buffer, int low, int high, int (*compar)(void **, void **, int, int, int, int), int int_flag, int reverse_flag, int fold_flag, int dir_flag);
void swap(void **a, void **b);
int readline(char **base, int max_lines);
int my_getline(char *line, int max_len);
void writeline(void **base, int len);
char *alloc(int len);
void afree(void **base, int len);
void get_substring(void **lineptr, void **buffer, int index, int nlines);
void extract_string(char *s, char *string);

int is_global_specified = 0;
int global_int_flag = 0;
int global_reverse_flag = 0;
int global_fold_flag = 0;
int global_dir_flag = 0;

int main(int argc, char *argv[]) {
    int int_flag[MAXLINES] = {0};
    int reverse_flag[MAXLINES] = {0};
    int fold_flag[MAXLINES] = {0};
    int dir_flag[MAXLINES] = {0};
    int fields[MAXLINES];
    int field_count = 0;
    int nlines;
    char *lineptr[MAXLINES];
    char *buffer[MAXLINES];

    if ((nlines = readline(lineptr, MAXLINES)) > 0) {
        parse_flags(argc, argv, int_flag, reverse_flag, fold_flag, dir_flag, fields, &field_count);

        if (is_global_specified) {
            printf("Sorting Globally, global_int_flag: %d, global_reverse_flag: %d, global_fold_flag: %d, global_dir_flag: %d\n", global_int_flag, global_reverse_flag, global_fold_flag, global_dir_flag);
            for (int i = 0; i < nlines; i++) {
                buffer[i] = lineptr[i];
            }
            quicksort((void **)lineptr, (void **)buffer, 0, nlines - 1,
                        global_int_flag ? cmp_num : cmp_str,
                        global_int_flag, global_reverse_flag, global_fold_flag, global_dir_flag);

            writeline((void **)lineptr, nlines);
        }

        for (int i = 0; i < field_count; i++) {
            int index = fields[i];
            printf("Sort on Field: %d, int_flag: %d, reverse_flag: %d, fold_flag: %d, dir_flag: %d\n", index, int_flag[index], reverse_flag[index], fold_flag[index], dir_flag[index]);
            get_substring((void **)lineptr, (void **)buffer, index, nlines);
            quicksort((void **)lineptr, (void **)buffer, 0, nlines - 1,
                        int_flag[index] ? cmp_num : cmp_str,
                        int_flag[index], reverse_flag[index], fold_flag[index], dir_flag[index]);
            writeline((void **)lineptr, nlines);
        }

        printf("Finished Sorting\n");
        // writeline((void **)lineptr, nlines);
        afree((void **)lineptr, nlines);
        afree((void **)buffer, nlines);

        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

void parse_flags(int argc, char **argv, int *int_flag, int *reverse_flag, int *fold_flag, int *dir_flag, int *fields, int *field_count) {
    int current_field = -1;
    for (int i = 1; i < argc; i++)

        if (argv[i][0] == '-' && isdigit(argv[i][1])) {
            int field = atoi(&argv[i][1]) - 1;
            fields[*field_count] = field;
            current_field = field;
            (*field_count)++;

            for (int j = 2; j < strlen(argv[i]); j++) {
                if (argv[i][j] == 'n') int_flag[current_field] = 1;
                if (argv[i][j] == 'r') reverse_flag[current_field] = 1;
                if (argv[i][j] == 'f') fold_flag[current_field] = 1;
                if (argv[i][j] == 'd') dir_flag[current_field] = 1;
            }
        }

        else if (argv[i][0] == '-') {
            for (int j = 1; j < strlen(argv[i]); j++) {
                if (current_field != -1) {
                    if (argv[i][j] == 'n') int_flag[current_field] = 1;
                    if (argv[i][j] == 'r') reverse_flag[current_field] = 1;
                    if (argv[i][j] == 'f') fold_flag[current_field] = 1;
                    if (argv[i][j] == 'd') dir_flag[current_field] = 1;
                }
                else {
                    is_global_specified = 1;
                    if (argv[i][j] == 'n') global_int_flag = 1;
                    if (argv[i][j] == 'r') global_reverse_flag = 1;
                    if (argv[i][j] == 'f') global_fold_flag = 1;
                    if (argv[i][j] == 'd') global_dir_flag = 1;
                }
            }

        }
}

void get_substring(void **lineptr, void **buffer, int index, int nlines) {
    for (int i = 0; i < nlines; i++) {
        char line[MAXLEN];
        strcpy(line, (char *)lineptr[i]);

        char *token = strtok(line, ",");
        int count = 0;

        while (token != NULL) {
            if (count == index) {
                buffer[i] = malloc(strlen(token) + 1);  // allocate memory
                if (buffer[i] != NULL) {
                    strcpy((char *)buffer[i], token);  // copy token into new memory
                } else {
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }
                printf("%s\n", (char *)buffer[i]);
                printf("%s\n", "************************");
                break;
            }
            token = strtok(NULL, ",");
            count++;
        }

        // If the desired column doesn't exist, set buffer[i] to an empty string
        if (token == NULL) {
            buffer[i] = malloc(1);
            if (buffer[i] != NULL) {
                ((char *)buffer[i])[0] = '\0';
            }
        }
    }
}



int cmp_num(void **a, void **b, int int_flag, int reverse_flag, int fold_flag, int dir_flag) {
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


int cmp_str(void **a, void **b, int int_flag, int reverse_flag, int fold_flag, int dir_flag) {
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

    int result;
    if (fold_flag) {
        printf("%s\n", "Applying fold_flag");
        result = strcasecmp(s1, s2);
    } else {
        result = strcmp(s1, s2);  
    }

    return reverse_flag ? -result : result;
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


void quicksort(void *base[], void *buffer[], int low, int high, int (*compar)(void **, void **, int, int, int, int), int int_flag, int reverse_flag, int fold_flag, int dir_flag) {
    if (low < high) {
        int p = partition(base, buffer, low, high, compar, int_flag, reverse_flag, fold_flag, dir_flag);
        quicksort(base, buffer, low, p, compar, int_flag, reverse_flag, fold_flag, dir_flag);
        quicksort(base, buffer, p + 1, high, compar, int_flag, reverse_flag, fold_flag, dir_flag);
    }
}

int partition(void **base, void **buffer, int low, int high, int (*compar)(void **, void **, int, int, int, int), int int_flag, int reverse_flag, int fold_flag, int dir_flag) {
    void **pivot = buffer + low;
    int left = low - 1;
    int right = high + 1;

    while (1) {
        do {
            right--;
        } while (compar(buffer + right, pivot, int_flag, reverse_flag, fold_flag, dir_flag) > 0);

        do {
            left++;
        } while (compar(buffer + left, pivot, int_flag, reverse_flag, fold_flag, dir_flag) < 0);

        if (left >= right)
            return right;

        swap(base + left, base + right);
        swap(buffer + left, buffer + right);
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
