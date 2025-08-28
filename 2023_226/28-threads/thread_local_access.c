#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

int* addrs[N];

_Thread_local int val;

void* func(void* smth) {
    int i = (int)(intptr_t)smth;
    addrs[i] = &val;
    printf("[%d]\tval: %d, addr: %p\n", i, val, &val);
    sleep(5);
    printf("[%d]\tval: %d, addr: %p\n", i, val, &val);
    return NULL;
}

int main() {
    pthread_t tids[N];
    for (int i = 0; i != N; ++i) {
        pthread_create(&tids[i], NULL, func, (void*)(intptr_t)i);
    }
    printf("[main]\tval: %d, addr: %p\n", val, &val);

    sleep(1);

    for (int i = 0; i != N; ++i) {
        *addrs[i] = i;
    }
    printf("New values:\n");

    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }
}
