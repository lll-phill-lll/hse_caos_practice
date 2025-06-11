#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define N 5


void *func(void *arg) {
    sleep(1);
    int i = *(int*)arg;
    // int i = (int)arg;

    // int i = (int)(intptr_t)arg;

    printf("Got number: %d\n", i);

    return NULL;
}

int main() {
    pthread_t tids[N];

    int i;
    for (i = 0; i < N; ++i) {
        pthread_create(&tids[i], NULL, func, &i);
        // pthread_create(&tids[i], NULL, func, (void*)i);
        // pthread_create(&tids[i], NULL, func, (void*)(intptr_t)i);

    }

    for (int i = 0; i < N; ++i) {
        pthread_join(tids[i], NULL);

    }


    return 0;
}

