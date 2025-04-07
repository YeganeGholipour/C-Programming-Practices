#include <stdio.h>

int sum_array(const int a[], int n) {
    int i, sum;

    sum = 0;
    for (i = 0; i < n; i++)
        sum += a[i];
    return sum;
}

int sum_array_pointer(const int *a, int n) {
    int sum = 0;
    const int *p;
    for (p = a; p < a + n; p++)
        sum += *p;
    return sum;
}

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int res = sum_array_pointer(arr, 10);
    printf("%d\n", res);
}