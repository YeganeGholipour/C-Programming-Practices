#include <stdio.h>

#define N 40

void fibonacci(int *b);

int main() {
    int arr[N] = {arr[0] = 0, arr[1] = 1};
    int *p;

    fibonacci(arr);

    for (p = arr; p <= arr + N; p++)
        printf("%d\n", *p);
}

void fibonacci(int *b) {
    for (int i = 2; i < N; i++) {
        b[i] = b[i-2] + b[i-1];
    }
}

