#include <stdio.h>

int main() {
    char a[2][3] = { "ab", "cd" };

    printf("a            = %p\n", (void *)a);
    printf("&a[0]        = %p\n", (void *)&a[0]);
    printf("a[0]         = %p\n", (void *)a[0]);
    printf("&a[0][0]     = %p\n", (void *)&a[0][0]);
    printf("&a           = %p\n", (void *)&a);
    printf("&a[0]        = %p\n", (void *)&a[0]);

    printf("\n--- Comparisons ---\n");

    printf("a == &a[0]          → %s\n", (a == &a[0]) ? "true" : "false");
    printf("a[0] == &a[0][0]    → %s\n", (a[0] == &a[0][0]) ? "true" : "false");
    printf("a != &a            → %s\n", (a != (char (*)[3])&a) ? "true" : "false");  // cast to silence warning
    printf("a[0] != &a[0]      → %s\n", (a[0] != (char *)&a[0]) ? "true" : "false"); // cast to match types

    return 0;
}
