#include <stdio.h>

int power(int a, int b) {
    int i, p;
    p = 1;

    for (i = 1; i <= b; i++) 
        p = p * a;
    
    return p;
}

int main() {
    int i, input;
    scanf("%d", &input);
    for (i = 0; i <= 10; i++) {
        printf("%d\n", power(input, i));
    }
}