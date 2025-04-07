#include <stdio.h>

int main() {
    char a[2][3] = {"ab", "cd"};
    /*

    {
    {'a', 'b', '\0'},
    {'c', 'd', '\0'}
    }
    
    - first is an array of type char[2][3]
    - first decays to char (*)[3] ---> a pointer to the first row
    - first[0] ---> a pointer to the first element of the first row of type char *
    - first[0][0] ----> the first element of the first row of type char

    */
    // char *second[2] = {"ab", "cd"};
    printf("a: %p\n", a);
    printf("&a: %p\n", &a);
    printf("position of a[1]: %p\n", a[1]);
    printf("value of a[1]: %s\n", a[1]);
    printf("value of a[1][0]: %c\n", a[1][0]);


    return 0;
}