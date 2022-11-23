#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

int* vals[N];

// _Thread_local int val;
int val = 1; // так у нас всё указывает на одну ячейку памяти, поэтому проходясь по массиву получим одно значение

void* func(void* smth) {
    int i = (int)(intptr_t)(smth);
    printf("%d:\t%p, %d\n", i, &val, val);
    vals[i] = &val;
    /* Засыпают все, кроме главного */
    sleep(10);

    printf("%d:\t%p, %d\n", i, &val, val);

    return NULL;
}

int main() {
    pthread_t tids[N];
    for (int i = 0; i != N; ++i) {
        pthread_create(&tids[i], NULL, func, (void *)(intptr_t)i);
    }

    printf("main:\t%p, %d\n", &val, val);
    /* Сном мы пытаемся синхроницироваться и сделать вид, что за это время поток отработает */
    sleep(3);
    for (int i = 0; i != N; ++i) {
        *vals[i] = 5 * i; // меняем значения
    }
    printf("main:\t%p, %d\n", &val, val);

    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }
}
