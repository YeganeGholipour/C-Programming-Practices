#include <stdio.h>

#define MAXLINE 1000
#define MAX 80

int strip(char s[]) {
    int j, i = 0;

    while (s[i] != '\0')
        i++;

    for (j = i - 1; j >= 0 && (s[j] == '\t' || s[j] == ' '); j--)
        s[j] = '\0';

    return j + 1;  // Return new length after stripping
}

int my_getline(char s[], int lim) {
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}

int main() {
    int len;
    char line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0) {
        int new_len = strip(line);
        printf("New length: %d\n", new_len);
        printf("Stripped line: '%s'\n", line); // Print stripped line for clarity

        if (new_len > MAX) {
            printf("%s\n", line);
        }
    }
    return 0;
}
