#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getline(char *line, int maxlen);
char *alloc(int len);

int main() {
    int nlines; /* number of input lines read */
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1); /* sort lines */
        writelines(lineptr, nlines); /* write sorted lines */
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p; /* store pointer to line */
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    int i;
    for (i = 0; i < nlines; i++) 
        printf("%s\n", lineptr[i]);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
    int i, last;
    if (left >= right) /* do nothing if array contains fewer than two elements */
        return;
    swap(v, left, (left + right) / 2); /* pivot: middle element */
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) /* compare strings */
            swap(v, ++last, i); /* swap if less than pivot */
    }
    swap(v, left, last); /* move pivot into correct position */
    qsort(v, left, last - 1); /* sort left partition */
    qsort(v, last + 1, right); /* sort right partition */
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* getline: read a line into s, return length */
int getline(char *s, int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

/* alloc: return a pointer to a space for len characters */
char *alloc(int len) {
    return (char *)malloc(len * sizeof(char));
}

/* TEST CASE */
int main_test() {
    char *test_input[] = {
        "banana\n",
        "apple\n",
        "cherry\n"
    };

    // Simulating readlines
    for (int i = 0; i < 3; i++) {
        lineptr[i] = test_input[i];
    }

    int nlines = 3;

    // Test sorting and output
    qsort(lineptr, 0, nlines - 1); /* sort lines */
    writelines(lineptr, nlines); /* write sorted lines */

    return 0;
}
