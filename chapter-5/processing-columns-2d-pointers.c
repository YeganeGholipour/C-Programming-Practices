#include <stdio.h>

int main(void) {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  // a one-dimensional array with 10 elements
    int (*p)[10];  // p is a pointer to an array of 10 integers
    
    p = &a;  // p points to the entire array 'a'
    
    // Now we can access elements in the array using p:
    for (int i = 0; i < 10; i++) {
        printf("%d ", (*p)[i]);  // Dereference p to get the array and access elements
    }
    
    return 0;
}
