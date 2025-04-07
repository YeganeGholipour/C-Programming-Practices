#include <stdio.h>

void baseConverter(int n, int base) {
    int remainder;
    int i = 0;
    char s[100];
    char hex[] = "0123456789ABCDEF";

    if (n == 0) {
        printf("0\n");
        return;
    }

    while (n != 0) {
        remainder = n % base;
        n /= base;
        s[i++] = hex[remainder];
    }

    int j;
    for (j = i - 1; j >= 0; j--) {
        printf("%c", s[j]);
    } 
    printf("\n");
}



int main() {
    int n = 343;
    baseConverter(n, 16);
}