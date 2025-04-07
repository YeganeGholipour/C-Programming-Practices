#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    int j = strlen(s) - 1, i = 0;
    char temp;
    while (i < j) {
        temp = s[i];
        s[i++] = s[j];
        s[j--] = temp;
    }
}


char* itob(int n, char s[], int base) {
    int remainder = 0;
    int i = 0;
    char numbers[] = "0123456789ABCDEF";

    if (n == 0)
        s[i++] = '0';

    while (n != 0) {
        remainder = n % base;
        s[i++] = numbers[remainder];
        n /= base;
    } 
    s[i] = '\0';
    reverse(s);
    return s;
}

int main() {
    char s[100];
    int n = 343;
    char *string = itob(n, s, 16);
    printf("%s\n", string);
}