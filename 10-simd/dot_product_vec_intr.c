#include <immintrin.h>

double dot_product_vec_intr(int n, double* vec1, double* vec2) {
    __m128d xmm0 = _mm_setzero_pd();

    int i = 0;
    for (; i <= n - 2; i += 2) {
        __m128d v1 = _mm_loadu_pd(&vec1[i]);
        __m128d v2 = _mm_loadu_pd(&vec2[i]);

        __m128d prod = _mm_mul_pd(v1, v2);

        xmm0 = _mm_add_pd(xmm0, prod);
    }

    if (i < n) {
        __m128d v1 = _mm_load_sd(&vec1[i]);
        __m128d v2 = _mm_load_sd(&vec2[i]);

        __m128d prod = _mm_mul_sd(v1, v2);

        xmm0 = _mm_add_sd(xmm0, prod);
    }

    // xmm0 = xmm0[0] + xmm0[1]
    xmm0 = _mm_hadd_pd(xmm0, xmm0);

    double result;
    // Сохраняем результат в обычную переменную
    _mm_store_sd(&result, xmm0);

    return result;
}
