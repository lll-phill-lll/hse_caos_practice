#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 2

pthread_t tids[N];

void* func(void* smth) {
    int i = (int)(intptr_t)(smth);
    int next_ind = (i + 1) % N;
    printf("%d waiting for %d\n", i, next_ind);
    pthread_join(tids[next_ind], NULL);
    return NULL;
}

int main() {
    tids[0] = pthread_self();
    for (int i = 1; i != N + 1; ++i) {
        pthread_create(&tids[i], NULL, func, (void *)(intptr_t)i);
    }

    printf("%d waiting for %d\n", 0, 1);
    pthread_join(tids[1], NULL);
}
