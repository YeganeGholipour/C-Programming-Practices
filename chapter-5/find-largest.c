#include <stdio.h>

int *find_largest(int a[], int n);

int main() {
    int b[] = {12, 55, 9, 6, 8, 45, 21, 64, 23, 92};
    int N = 10;
    int *p;

    p = find_largest(b, N);
    printf("Largest: %d\n", *p);

    return 0;
}

int *find_largest(int a[], int n) {
    int *largest = &a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] > *largest)
            largest = &a[i];
    }

    return largest;
}