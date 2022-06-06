#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

_Thread_local int val;
// int val;

void* func(void* smth) {
    printf("%p\n", (void*)&val);
    return NULL;
}

int main() {
    pthread_t tids[N];
    for (int i = 0; i != N; ++i) {
        pthread_create(&tids[i], NULL, func, NULL);
    }

    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }
}
