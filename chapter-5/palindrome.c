#include <stdio.h>
#include <string.h>
#include <ctype.h>

int palindrome(char *string, int n) {
    fgets(string, n, stdin); 
    int len = strlen(string);
    if (string[len - 1] == '\n') {  
        string[len - 1] = '\0';
    }

    char reverse[n];
    char *p = string + len - 1, *q = reverse;

    while (p >= string) {
        if (isalpha(*p)) {
            *q++ = *p;
        }
        p--;
    }
    *q = '\0'; 

    char *string_p = string;
    char *reverse_p = reverse;

    while (*string_p != '\0' && *reverse_p != '\0') {
        if (*string_p != *reverse_p) {
            printf("Not a palindrome\n");
            return 1;
        }
        string_p++;
        reverse_p++;
    }

    if (*reverse_p != '\0') {
        printf("Not a palindrome\n");
        return 1;
    }

    printf("It is a palindrome\n");
    return 0;
}

int main() {
    char string[100];
    palindrome(string, 100);
    return 0;
}
