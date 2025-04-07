#include <stdio.h>

int main(void) {
    int digit_seen[10] = {0}; 
    int digit, number;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (number < 0)  
        number = -number;

    while (number > 0) {
        digit = number % 10;
        digit_seen[digit]++; 
        number /= 10; 
    }

    printf("\nDigit:      ");
    for (int i = 0; i < 10; i++) {
        printf("%3d", i);
    }

    printf("\nOccurrences:");
    for (int i = 0; i < 10; i++) {
        printf("%3d", digit_seen[i]);
    }

    printf("\n");

    return 0;
}
