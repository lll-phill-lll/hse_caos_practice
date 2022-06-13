#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 2

void somefunc(int i) {
    printf("%d\n", i);
    somefunc(++i);
}

void* func(void* smth) {
    somefunc(0);
    return NULL;
}

int main() {
    pthread_t tids[N];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);

    /* создаем кучу потоков с рекурсией и ждем сегфолта */
    for (int i = 0; i != N; ++i) {
        pthread_create(&tids[i], &attr, func, NULL);
    }
    pthread_attr_destroy(&attr);

    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }
}
