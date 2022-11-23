#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* smth) {
    printf("hello\n");
    return NULL;
}

int main() {
    pthread_t tid;
    sleep(10);
    while(1)
    pthread_create(&tid, NULL, func, NULL);
}
