#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <pthread.h>

#define N 5

_Thread_local volatile sig_atomic_t val;

void* func(void* smth) {
    int i = (int)(intptr_t)(smth);
    pthread_t self_tid = pthread_self();
    while(1) {
        sleep(1);
        /* Печатаем сигнал и идентификатор */
        printf("%d %ld: %d\n", i, self_tid, val);
        if (val) {
            return NULL;
        }
    }
    return NULL;
}

void handler(int n) {
    val = 1; // Флаг чтобы понять, что к нам пришел сигнал и выставим мы его в том потоке, куда сигнал пришет
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    sigaction(SIGINT, &sa, NULL);

    pthread_t tids[N];

    for (int i = 0; i != N; ++i) {
        /* Создаем потоки и у них общая память */
        pthread_create(&tids[i], NULL, func, (void *)(intptr_t)i);
        printf("tid: %ld\n", tids[i]);
    }

    sigset_t s;
    sigfillset(&s);
    /* Для правильной работы в нескольких потоках */
    pthread_sigmask(SIG_BLOCK, &s, NULL);

    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }
}
