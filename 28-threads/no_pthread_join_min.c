
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* smth) {
    printf("hello\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    pthread_attr_setguardsize(&attr, 0);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int count = 0;
    while(1) {
        if (pthread_create(&tid, &attr, func, NULL) != 0) {
            perror("");
            printf("Can't create thread. Created: %d\n", count);


            sleep(3);

        } else {
            ++count;
        }
    }

    pthread_attr_destroy(&attr);
}
