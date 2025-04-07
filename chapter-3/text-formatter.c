#include <stdio.h>
#include <string.h>
#include <ctype.h>

void formatText(char s[], int n) {
    int i = 0, length = 0, start = 0;
    
    while (s[i] != '\0') {
        // Skip leading spaces
        while (s[i] == ' ') 
            i++;

        // Mark the start of a word
        start = i;
        
        // Find the length of the next word
        int wordLength = 0;
        while (s[i] != ' ' && s[i] != '\0') {
            wordLength++;
            i++;
        }

        // If adding this word exceeds line length, move to a new line
        if (length > 0 && length + wordLength + 1 > n) {
            printf("\n");
            length = 0;
        }

        // Print the word
        if (length > 0) {
            printf(" ");  // Add space between words if not at the start of a line
            length++;
        }

        for (int j = start; j < start + wordLength; j++) {
            printf("%c", s[j]);
        }

        length += wordLength;
    }
    printf("\n"); // Final newline for formatting
}

int main() {
    char text[] = "Hello Amazing World ThisIsALongWord";
    int N = 10;
    formatText(text, N);
    return 0;
}
