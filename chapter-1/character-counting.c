#include <stdio.h>

// int main() {
//     int c;
//     long i;
//     i = 0;
//     while ((c=getchar()) != EOF && c != '\n') {
//         i++;
//     }
//     printf("Counts: %ld\n", i);
// }

int main() {
    long i;
    for (i=0; getchar()!=EOF; ++i)
        ;
    printf("Counts: %ld\n", i);
}