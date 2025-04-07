#include <stdio.h>

void store_zeros(int a[], int n) {
    int *p;
    for (p = a; p < a + n; p++)
        *p = 0;
}

int main() {
    int arr[10];
    store_zeros(arr, 10);
    int *p;
    for (p = arr; p < arr + 10; p++)
        printf("%d\n", *p);
}