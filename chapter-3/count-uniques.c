#include <stdio.h>

void countCharacters(char str[]) {
    int freq[256] = {0};
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ')
            freq[str[i]]++;
        i++;
    }

    printf("{");
    i = 0;
    while (i < 256) {
        if (freq[i] > 0) {
            printf("%c:%d, ", i, freq[i]);
        }
        i++;
    }
    printf("\b\b }\n");
}

int main() {
    char str[] = "hello world";
    countCharacters(str);
    return 0;
}