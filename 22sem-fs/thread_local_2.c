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
    	/*
    	  int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);

    	*/
        pthread_create(&tids[i], NULL, func, NULL);
    }

    for (int i = 0; i != N; ++i) {
        /* Дожидаемся выполнения каждого потока. Всего их будет n+1 так как еще main */
        pthread_join(tids[i], NULL);
    }
}
