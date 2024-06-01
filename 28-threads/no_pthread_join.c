#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* smth) {
    pthread_detach(pthread_self());
    printf("hello\n");
    return NULL;
}

int main() {
    pthread_t tid;
    while(1) {
        if (pthread_create(&tid, NULL, func, NULL) != 0) {
            printf("Can't create thread\n");
            sleep(3);

        }
    }
}
