#include <stdio.h>

int main() {
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\t')  // Check for tab character
            putchar('\t');  // Output the tab character
        else if (c == '\b')  // Check for backspace character
            putchar('\b');  // Output the backspace character
        else if (c == '\\')  // Check for backslash character
            putchar('\\');  // Output the backslash character
        else
            putchar(c);  // Output any other character as it is
    }
}
