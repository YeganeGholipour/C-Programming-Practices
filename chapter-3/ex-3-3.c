#include <stdio.h>
#include <string.h>

void expand(char s1[], char s2[]) {
    int i = 0, j = 0;

    while (s1[i] != '\0') {
        if (s1[i + 1] == '-' && s1[i + 2] != '\0') { 
            char start = s1[i];
            char end = s1[i + 2];

            if ((start >= 'a' && start <= 'z' && end >= 'a' && end <= 'z' && end >= start) ||
                (start >= 'A' && start <= 'Z' && end >= 'A' && end <= 'Z' && end >= start) ||
                (start >= '0' && start <= '9' && end >= '0' && end <= '9' && end >= start)) {
                
                for (char c = start; c <= end; c++) {
                    s2[j++] = c;
                }
                i += 3; 
                continue;
            }
        }

        s2[j++] = s1[i++];
    }

    s2[j] = '\0'; 
}

int main() {
    char s2[100];

    expand("a-d0-3X-Z", s2);
    printf("%s\n", s2); // Expected: "abcd0123XYZ"

    expand("-a-c", s2);
    printf("%s\n", s2); // Expected: "-abc"

    expand("A---Z", s2);
    printf("%s\n", s2); // Expected: "A---Z" (invalid range, treated literally)

    expand("a-z-0-9", s2);
    printf("%s\n", s2); // Expected: "abcdefghijklmnopqrstuvwxyz-0123456789"

    expand("b-g", s2);
    printf("%s\n", s2); // Expected: "bcdefg"

    expand("Z-A", s2);
    printf("%s\n", s2); // Expected: "Z-A" (invalid range, copied as-is)

    return 0;
}
