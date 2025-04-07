#include <stdio.h>


int main() {
    char *p = "a";
    /*
    
    p points to a character ---> it points to character 'a' in the {'a', '\0'}
    so *p is just 'a'
    */

    char arr[2][3] = {{'a', 'b', 'c'}, {'d', 'e', 'f'}};

    printf("%s\n", *(arr + 1));

    printf("*p: %c\n", *p);   // ✅ prints: *p: a
    printf("p: %s\n", p);     // ✅ prints: p: a
    printf("p[0]: %c\n", p[0]);
    printf("p: %p\n", p);
}