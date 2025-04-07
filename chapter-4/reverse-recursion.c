#include <stdio.h>
#include <string.h>

void reverse(char s[], int *i, int *j) {
    if (*i >= *j) {  // Base case: when `i` crosses `j`, stop
        return;
    }

    // Swap characters
    char temp = s[*i];
    s[*i] = s[*j];
    s[*j] = temp;

    // Move indices towards center
    (*i)++;
    (*j)--;

    // Recurse
    reverse(s, i, j);
}

int main() {
    char s[] = "hello";
    int i = 0, j = strlen(s) - 1;

    reverse(s, &i, &j);
    printf("%s\n", s); // Expected output: "olleh"

    return 0;
}
