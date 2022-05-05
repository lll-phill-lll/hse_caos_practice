#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double dot_product_c(int n, double* x, double *y) {
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

    int n = 30000000;
    int iters = 100;
    double* vec1 = malloc(n * sizeof (double));
    double* vec2 = malloc(n * sizeof (double));
    for (int i = 0; i != n; ++i) {
        vec1[i] = (rand() % 1000) / 3.14;
        vec2[i] = (rand() % 1000) / 3.14;
    }
    // for (int i = 0; i != n; ++i) {
    //     printf("%lf ", vec1[i]);
    // }
    // printf("\n");

    // for (int i = 0; i != n; ++i) {
    //     printf("%lf ", vec2[i]);
    // }
    // printf("\n");

    clock_t t;

    double res;
    double time_taken;

    t = clock();

    for (int i = 0; i != iters; ++i) {
        res = dot_product_c(n, vec1, vec2);
    }
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("c:\t\t %lf, time: %lf sec\n", res, time_taken);

    t = clock();
    for (int i = 0; i != iters; ++i) {
        res = dot_product(n, vec1, vec2);
    }
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("unpacked:\t %lf, time: %lf sec\n", res, time_taken);

    t = clock();
    for (int i = 0; i != iters; ++i) {
        res = dot_product_vec(n, vec1, vec2);
    }
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("packed:\t\t %lf, time: %lf sec\n", res, time_taken);
}
