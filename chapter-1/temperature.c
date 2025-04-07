#include <stdio.h>
#define LOWER 0
#define UPPER 300
#define STEP 20

// int main() {
//     float f, c;
//     f = 0;
//     printf("%s\t%s\n\n", "Fahr", "celsius");
//     while (f<=300) {
//         c = 5 * (f-32) / 9;
//         printf("%3.0f\t%6.1f\n", f, c);
//         f += 20;
//     }
//     return 0;
// }

// int main() {
//     float f, c;
//     printf("%s\t%s\n\n", "Fahr", "celsius");
//     for (f = 0; f <= 300; f += 20) {
//         c = 5 * (f-32) / 9;
//         printf("%3.0f\t%6.1f\n", f, c);
//     }
//     return 0;
// }

// int main() {
//     float f, c;
//     printf("%s\t%s\n\n", "Fahr", "celsius");
//     for (f = 300; f >= 0; f -= 20) {
//         c = 5 * (f-32) / 9;
//         printf("%3.0f\t%6.1f\n", f, c);
//     }
//     return 0;
// }

int main() {
    float f, c;
    printf("%s\t%s\n\n", "Fahr", "celsius");
    for (f=LOWER; f <= UPPER; f += STEP) {
        c = 5 * (f-32) / 9;
        printf("%3.0f\t%6.1f\n", f, c);
    }
    return 0;
}