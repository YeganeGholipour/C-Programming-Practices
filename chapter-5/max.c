#include <stdio.h>

int *max(int *a, int *b) {
    if (*a > *b)
        return a;
    else
        return b;
}


int main() {
    int *p, i , j;
    i = 12;
    j = 52;
    p = max(&i, &j);
}