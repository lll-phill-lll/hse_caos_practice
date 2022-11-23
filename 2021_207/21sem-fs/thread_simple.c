#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* func(void* smth) {
    printf("hello\n");
    return NULL;
}

int main() {
    pthread_t id = pthread_self();

    int err = pthread_join(id, NULL);
    printf("%d\n", err);
    // code

    // pthread_exit(NULL);
}
