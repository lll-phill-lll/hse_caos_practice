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
    int count = 0;
    while(1) {
        if (pthread_create(&tid, NULL, func, NULL) != 0) {
            printf("Can't create thread: %d\n", count);
            sleep(3);

        }
        ++count;
    }
}
