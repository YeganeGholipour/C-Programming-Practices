#include <stdio.h>

#define N 100

char *reverse_string(char *message, int length) {
    char c;
    int i = 0;

    while ((c = getchar()) != EOF && c != '\n' && i < length)
    {
        message[i++] = c;
    }
    message[i] = '\0';

    char *p = message, *q = message + i - 1;
    while (p < q) {
        char temp;
        temp = *q;
        *q-- = *p;
        *p++ = temp;
    }

    return message;
}

int main() {
    char m[N];
    char *res = reverse_string(m, N);
    for (int i = 0; i < N; i++)
    {
        printf("%c", res[i]);
    }
    printf("\n");
    
}