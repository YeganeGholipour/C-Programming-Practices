#include <stdio.h>
#include <ctype.h>

int getint(int *pt) {
    int c, sign = 1;

    // Skip non-digit characters
    while ((c = getchar()) != EOF && !isdigit(c) && c != '+' && c != '-');

    if (c == EOF) 
        return EOF;  // Return EOF if no more input

    // Handle sign
    if (c == '+' || c == '-') {
        sign = (c == '-') ? -1 : 1;
        c = getchar(); // Read next character
    }
    
    if (!isdigit(c)) 
        return 0;  // Not a valid number

    // Read the number
    *pt = 0;
    while (isdigit(c)) {
        *pt = 10 * (*pt) + (c - '0');
        c = getchar();
    }

    *pt *= sign;
    return 1;
}

int main() {
    int SIZE = 10;
    int numbers[SIZE];
    int n = 0;

    while (n < SIZE && getint(&numbers[n]) != EOF) {
        n++;
    }

    for (int i = 0; i < n; i++) {
        printf("array[%d] = %d\n", i, numbers[i]);
    }

    return 0;
}
