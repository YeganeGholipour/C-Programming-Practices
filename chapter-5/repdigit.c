#include <stdio.h>

int main(void) {
    int digit_seen[10] = {0}; 
    int digit, number;
    int has_repeated = 0; 

    printf("Enter a number: ");
    scanf("%d", &number);

    if (number < 0)  
        number = -number;

    while (number > 0) {
        digit = number % 10;
        digit_seen[digit]++; 
        number /= 10; 
    }

    printf("Repeated digits: ");
    for (int i = 0; i < 10; i++) {
        if (digit_seen[i] > 1) { 
            printf("%d ", i);
            has_repeated = 1;
        }
    }

    if (!has_repeated)
        printf("None"); 

    printf("\n");

    return 0;
}
