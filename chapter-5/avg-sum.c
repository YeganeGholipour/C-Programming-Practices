#include <stdio.h>

#define N 10

void avg_sum(double a[], int n, double *avg, double *sum);

int main() {
    int i;
    double b[N], avg, sum;

    for(i = 0; i < N; i++) {
        scanf("%lf", &b[i]);
    }

    avg_sum(b, N, &avg, &sum);

    printf("SUM: %lf\n", sum);
    printf("AVG: %lf\n", avg);
    
}

void avg_sum(double a[], int n, double *avg, double *sum) {
    *sum = 0;
    for (int i = 0; i < n; i++) {
        *sum += a[i];
    }
    *avg = *sum / n;
}