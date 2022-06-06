#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

void* func(void* smth) {
    int i = (int)(intptr_t)(smth);
    int num;
    while(1) {
        scanf("%d", &num);
        sleep(1);
        printf("%d %d\n", i, num);
    }
    return NULL;
}

int main() {
    pthread_t tids[N];
    for (int i = 0; i != N; ++i) {
        pthread_create(&tids[i], NULL, func, (void *)(intptr_t)i);
    }

    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }
}
