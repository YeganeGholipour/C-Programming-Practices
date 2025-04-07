#include <stdio.h>
#include <string.h>

void my_strncpy(char *s, char *t, int n);

void my_strncpy(char *s, char *t, int n) {
    int len = strlen(t) + 1;  // Include null terminator
    printf("Length of string including null terminator: %d\n", len);

    // If n is greater than length, we only copy up to the full string
    if (n > len) {
        printf("Only copies for the length of second string.\n");
        n = len;
    }

    // Copy up to n characters (may include the null terminator if n == len)
    while (n-- > 0) {
        *s++ = *t++;
    }

    // No need for extra null terminator if already copied '\0',
    // but this check is safe in case n < len and no '\0' was copied
    if (*(s - 1) != '\0') {
        printf("Manually adding null terminator.\n");
        *s = '\0';
    }
}

int main() {
    char string1[100];
    char string2[] = "happy birthday";
    
    my_strncpy(string1, string2, 15);
    printf("Result: %s\n", string1);
}
