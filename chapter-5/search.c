#include <stdio.h>
#include <stdbool.h>

bool search(const int a[], int n, int key) {
    int const *p;
    
    for (p = a; p < a + n; p++) {
        if (*p == key)
            return true;
    }
    return false;
}

int main() {
    int arr[] = {54, 5, 97, 2, 3, 9, 77, 2};
    bool res = search(arr, 8, 9);
    printf("res: %d\n", res);
}