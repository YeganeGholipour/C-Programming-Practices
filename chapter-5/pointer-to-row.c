#include <stdio.h>

int main() {
    int (*p)[5];  // p is declared but uninitialized
    printf("Address stored in p before initialization: %p\n", (void*)p);


    int a[3][5];  // A 2D array with 3 rows and 5 columns
    p = a;  // Now p points to the first row (a[0])
    printf("Address stored in p after initialization: %p\n", (void*)p);
    printf("The address of the first element of the first row is: %p\n", &a[0][0]);
    
    return 0;
}
