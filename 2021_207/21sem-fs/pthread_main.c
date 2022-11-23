#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* smth) {
    printf("hello\n");
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, main, NULL);
}
