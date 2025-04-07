#include <stdio.h>

void mystrncpy(char src[], char dest[], int n) {
    int i = 0;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i++] = '\0';
    }
}

int main() {
    char a[100];
    mystrncpy("hello", a, 10);
    printf("%s\n", a);
}