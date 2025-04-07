#include <stdio.h>

void find_two_largest(int a[], int n, int *largest, int *second_largest);

int main() {
    int N = 10, first, second;
    int b[] = {12, 55, 9, 6, 8, 45, 21, 64, 23, 92};

    find_two_largest(b, N, &first, &second);
    printf("First Largest: %d\n", first);
    printf("Second Largest: %d\n", second);

}

void find_two_largest(int a[], int n, int *largest, int *second_largest) {
    *largest = a[0];
    *second_largest = a[1];
    
    for (int i = 2; i < n; i++) {
        if (a[i] > *largest)
            *largest = a[i];
        else if (a[i] > *second_largest)
            *second_largest = a[i];
    }

}