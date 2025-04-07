#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

int readlines(char lines[][MAXLEN], int maxlines);
void writelines(char lines[][MAXLEN], int nlines);
void swap(char v[][MAXLEN], int i, int j);
void qsort(char v[][MAXLEN], int left, int right);
int getline(char *s, int lim);

int main() {
    int nlines;
    char lines[MAXLINES][MAXLEN];

    if ((nlines = readlines(lines, MAXLINES)) > 0) {
        qsort(lines, 0, nlines - 1);
        writelines(lines, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

// Reads lines into the 2D array
int readlines(char lines[][MAXLEN], int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    nlines = 0;

    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines)  // Make sure we don't exceed the maxlines
            return -1;
        else {
            line[len - 1] = '\0';  // Remove newline
            strcpy(lines[nlines++], line);  // Store the line
        }
    }
    return nlines;
}

// Writes each line to standard output
void writelines(char lines[][MAXLEN], int nlines) {
    for (int i = 0; i < nlines; i++) 
        printf("%s\n", lines[i]);
}

// Swaps two lines in the 2D array
void swap(char v[][MAXLEN], int i, int j) {
    char temp[MAXLEN];
    strcpy(temp, v[i]);
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

// Quicksort for sorting the lines
void qsort(char v[][MAXLEN], int left, int right) {
    int i, last;
    if (left >= right)
        return;
    
    swap(v, left, (left + right) / 2);
    last = left;
    
    for (i = left + 1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

// Custom getline to read a line
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
