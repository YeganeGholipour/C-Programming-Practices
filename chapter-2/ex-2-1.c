#include <stdio.h>
#include <limits.h>

int main() {
    printf("Signed char range: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned char range: 0 to %d\n", UCHAR_MAX);
    printf("Signed short range: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short range: 0 to %d\n", USHRT_MAX);
    printf("Signed int range: %d to %d\n", INT_MIN, INT_MAX);
    printf("Unsigned int range: 0 to %u\n", UINT_MAX);
    printf("Signed long range: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long range: 0 to %lu\n", ULONG_MAX);
    
    return 0;
}
