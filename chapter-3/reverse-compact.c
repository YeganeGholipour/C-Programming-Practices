#include <stdio.h>

void reversecompact(char s[]) {
    int i = 0;
    int start = 0;
    while (s[i] != '\0') {
        start = i;
        while (s[i + 1] != '\0' && s[i] + 1 == s[i + 1]){
            i++;
        }

        if (start != i) {
            printf("%c-%c", s[start], s[i]);
        } else {
            printf("%c", s[start]);
        }

        if (s[i+1] != '\0') {
            printf(",");
        }
        i++;
    }
}

int main() {
    char str[] = "abcdefgh";
    reversecompact(str);  // Output: a-h
    return 0;
}