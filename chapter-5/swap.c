#include <stdio.h>

void swap(int *p, int *q);

int main() {
    int i = 12;
    int j = 55;
    swap(&i, &j);
    printf("i is now: %d\n", i);
    printf("j is now: %d\n", j);
}

void swap(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}