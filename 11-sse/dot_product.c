#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double dot_product_c(int n, double* x, double* y) {
    double sum = 0;
    for (int i = 0; i != n; ++i) {
        sum += *x * *y;
        ++x;
        ++y;
    }
    return sum;
}

double dot_product(int, double*, double*);
double dot_product_vec(int, double*, double*);

int main() {
    srand(time(NULL));

    int n = 3;
    double* vec1 = malloc(n * sizeof(double));
    double* vec2 = malloc(n * sizeof(double));
    for (int i = 0; i != n; ++i) {
        vec1[i] = (rand() % 1000) / 3.14;
        vec2[i] = (rand() % 1000) / 3.14;
    }

    for (int i = 0; i != n; ++i) {
        printf("%lf ", vec1[i]);
    }
    printf("\n");

    for (int i = 0; i != n; ++i) {
        printf("%lf ", vec2[i]);
    }
    printf("\n");

    double res;
    res = dot_product_c(n, vec1, vec2);
    printf("c:\t %lf\n", res);

    res = dot_product(n, vec1, vec2);
    printf("asm:\t %lf\n", res);

    res = dot_product_vec(n, vec1, vec2);
    printf("packed:\t %lf\n", res);

    free(vec1);
    free(vec2);
}
