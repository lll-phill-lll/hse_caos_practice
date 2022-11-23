#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define N 5

int* results;
pthread_t* threads;

int main() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);


    threads = calloc(nthreads, sizeof(*threads));
    for (int i = 0; i < nthreads; ++i) {
        pthread_create(threads + i, &attr, task, (void *)(intptr_t)i);
    }
    pthread_attr_destroy(&attr);


    pthread_join(threads[nthreads - 1], NULL);
    for (int i = 0; i < nthreads; ++i) {
        printf("%d\n", results[i]);
    }
}
