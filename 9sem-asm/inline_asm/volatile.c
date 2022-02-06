#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    enum { N = 5 };
    uint64_t timestamps[N];
    for (size_t i = 0; i < N; ++i) {
        uint32_t eax, edx;
        asm
#ifdef VOLATILE
        volatile
#endif
        (
            "rdtsc\n"  // https://ru.wikipedia.org/wiki/Rdtsc
            : "=a"(eax), "=d"(edx)
        );
        timestamps[i] = ((uint64_t) edx << 32) + eax;
    }
    for (size_t i = 0; i < N; ++i) {
        printf("timestamps[%zu] = %"PRIu64"\n", i, timestamps[i]);
    }
}
