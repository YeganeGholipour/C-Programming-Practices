#include <stdio.h>

double inner_product(const double *a, const double *b, int n) {
    const double *ap, *bp;
    double sum = 0.0;

    for (ap = a, bp = b; ap < a + n && bp < b + n; ap++, bp++) {
        sum += *ap * *bp;
    }

    return sum;
}

int main() {
    double a[5] = {1.0, 2.5, 5.6, 6.0, 9.0};
    double b[5] = {8.55, 65.5, 9.0, 4.0, 2.0};

    double res = inner_product(a, b, 5);
    printf("%lf\n", res);
}