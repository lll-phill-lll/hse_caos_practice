#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Point {
    int i;

    int result;
};


void* func(void* arg) {
    struct Point* point = (struct Point*)arg;
    
    point->result = point->i * point->i;

    return &point->result;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Pass num of threads\n");
        return 1;
    }
    int num_threads = atoi(argv[1]);

    pthread_t* threads = calloc(num_threads, sizeof(*threads));

    struct Point* args = calloc(num_threads, sizeof(*args));


    for (int i = 0; i < num_threads; i++) {
        args[i].i = i;
        pthread_create(&threads[i], NULL, func, (void*)&args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        void* result;
        pthread_join(threads[i], &result);
        printf("Result: %d\n", *(int*)result);
    }

    free(threads);
    free(args);

    return 0;
}

