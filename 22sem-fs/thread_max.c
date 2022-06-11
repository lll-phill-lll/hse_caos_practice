#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* smth) {
    sleep(2);
    return NULL;
}

int main() {

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int i = 0;

    /*Создаем потоки пока можем*/
    while(1) {
        pthread_t tid;
        int res = pthread_create(&tid, &attr, func, NULL);
        if (res) {
            printf("Created %d threads\n", i);
            sleep(1);
            // return 0;
        } else {
            ++i;
        }
    }
    pthread_attr_destroy(&attr);
}
