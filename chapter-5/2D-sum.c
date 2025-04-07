#include <stdio.h>

#define LEN 4
int sum_two_dimensional_array(const int a[][LEN], int n) { // similart to (p = a[0]; p < a[0] + n * LEN; p++)
    int const *p;
    int sum = 0;

    for (p = &a[0][0]; p < &a[0][0] + n * LEN; p++)
        sum += *p;
    return sum;
}

int main() {
    int a[3][4] = { 
        {1, 2, 3, 4}, 
        {5, 6, 7, 8}, 
        {9, 10, 11, 12} 
    };

    int res = sum_two_dimensional_array(a, 3);
    printf("%d\n", res);
}