#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    char temp;
    int i = 0;
    int j = strlen(s) - 1;
    while (i < j) {
        temp = s[i];
        s[i++] = s[j];
        s[j--] = temp;
    }
}


char* itoa(int n, char s[], int base) { //return type is important
    int remainder, i = 0 ; 
    char digits[] = "0123456789ABCDEF";
    
    if (n == 0) {
        s[i++] = '0';
    }

    while (n != 0) {
        remainder = n % base;
        n /= base;
        s[i++] = digits[remainder];
    }
    s[i] = '\0';
    reverse(s);
    return s;
}



int main() {
    char s[100];
    int n = 343;
    char *new_s = itoa(n, s, 16); //important
    printf("%s\n", new_s);
}