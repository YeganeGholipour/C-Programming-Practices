#include <stdio.h>
#include <ctype.h>

#define SIZE 10  // Define size of array

int getch(void);        // Function to get a character from input
void ungetch(int);      // Function to push a character back into the input buffer

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    int c, sign;

    // Skip white spaces
    while (isspace(c = getch()))
        ;

    // If the character is not a digit or EOF, or not a sign, it is not a valid number
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);  // Push the character back into the buffer
        return 0;    // Return 0 to indicate no valid number
    }

    // Set the sign for the number (+ or -)
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') 
        c = getch();  // Get the next character

    // Read the digits and convert to an integer
    for (*pn = 0; isdigit(c); c = getch()) 
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;  // Apply the sign to the number

    // If the character is not EOF, push it back into the buffer
    if (c != EOF)
        ungetch(c);

    return c;  // Return the character that was last processed
}

// Input buffer for getch() and ungetch()
#define BUFSIZE 100
char buf[BUFSIZE];   // Buffer to store input
int bufp = 0;        // Pointer to the next free position in the buffer

// getch: Get a character from the input buffer or from stdin
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// ungetch: Push a character back into the input buffer
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main() {
    int n, array[SIZE];

    // Fill the array using getint
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;

    // Print the integers stored in the array
    for (int i = 0; i < n; i++)
        printf("array[%d] = %d\n", i, array[i]);

    return 0;
}
