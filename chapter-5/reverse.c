#include <stdio.h>

#define N 10

int main() {
    int a[N], *p;

    for (p = a; p < a + N; p++)
        scanf("%d", p);

    for (p = a + N; p >= a; p--)
        printf(" %d", *p);
        // printf("\n")
    printf("\n");

    return 0;
}