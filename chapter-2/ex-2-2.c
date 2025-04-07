#include <stdio.h>

int main() {
    int c, i = 0, lim = 100;
    char s[100];
    
    while (i < lim - 1) {
        c = getchar();  
        
        if (c != '\n' && c != EOF) {
            s[i] = c;  // Store the character
            i++;  // Increment the index
        } else {
            break;  // Exit loop if newline or EOF is encountered
        }
    }
    s[i] = '\0';  // Null-terminate the string (optional, depending on how you want to use it)
    
    printf("Input string: %s\n", s);
    return 0;
}
