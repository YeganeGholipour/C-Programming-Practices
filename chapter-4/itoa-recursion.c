#include <stdio.h>

void itoa_recursive(int n, int base, int *i, char s[]) { 
    char digits[] = "0123456789ABCDEF";

    if (n == 0) {
        return;
    }

    int remainder = n % base;
    itoa_recursive(n / base, base, i, s); 
    s[(*i)++] = digits[remainder]; 
}

char* itoa(int n, int base, char s[]) {
    int i = 0;
    
    if (n == 0) {
        s[i++] = '0'; 
    } else {
        itoa_recursive(n, base, &i, s);
    }

    s[i] = '\0'; 
    return s;
}

int main() {
    char s[100];
    int n = 347;
    char *result = itoa(n, 16, s);
    printf("%s\n", result); 
}
