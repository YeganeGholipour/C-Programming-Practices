#include <stdio.h>

void ident(int *a, int n) {
    int count = 0;
    for (int *p = a; p < a + n * n; p++, count++) {  
        *p = (count % (n + 1) == 0) ? 1 : 0;
    }
}

int main() {
    int arr[10][10];

    ident(&arr[0][0], 10);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf("%3d", arr[i][j]);
        printf("\n");  
    }

    return 0;
}
