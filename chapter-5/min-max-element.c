#include <stdio.h>

#define N 10


void max_min(int a[], int n, int *max, int *min);

int main() {
    int i, b[N], big, small;
    printf("Enetr %d numbers: ", N);
    for (i = 0; i < N; i++)
        scanf("%d", &b[i]);

    max_min(b, N, &big, &small);

    printf("Largest: %d\n", big);
    printf("Smallest: %d\n", small);

    return 0;
}


void max_min(int a[], int n, int *max, int *min) {
    *min = *max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > *max)
            *max = a[i];
        else if (a[i] < *min)
            *min = a[i];
    }
}