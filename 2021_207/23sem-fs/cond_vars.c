#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

volatile int f;

void* go_wait(void* smth) {
    pthread_mutex_lock(&m);
    printf("waiting\n");
    if (!f) {
        sleep(1);
        pthread_cond_wait(&c, &m);
        printf("got signal\n");
    } else {
        printf("missed signal\n");
    }
    pthread_mutex_unlock(&m);
}

void* go_signal(void* smth) {
    pthread_mutex_lock(&m);
    f = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}


int main() {

    pthread_t wait_pid, signal_pid;
    pthread_create(&wait_pid, NULL, go_wait, NULL);
    pthread_create(&signal_pid, NULL, go_signal, NULL);

    pthread_join(wait_pid, NULL);
    pthread_join(signal_pid, NULL);
}
