#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define SEC 3

void* thread_function(void* arg) {
    pthread_exit(NULL);
}

void process_function() {
    _exit(0);
}

void measure_threads() {
    pthread_t thread;
    int count = 0;
    time_t start = time(NULL);

    while (time(NULL) - start < SEC) {
        if (pthread_create(&thread, NULL, thread_function, NULL) == 0) {
            count++;
            pthread_detach(thread);
        }
    }

    printf("Threads created per second: %d\n", count / SEC);
}


void measure_processes() {
    int count = 0;
    time_t start = time(NULL);

    while (time(NULL) - start < SEC) {
        pid_t pid = fork();
        if (pid == 0) {
            process_function();
        } else if (pid > 0) {
            count++;
        }
    }

    for (int i = 0; i < count; ++i) {
        wait(NULL);
    }

    printf("Processes created per second: %d\n", count / SEC);
}

int main() {
    printf("Measuring thread creation speed...\n");
    measure_threads();

    printf("Measuring process creation speed...\n");
    measure_processes();

    return 0;
}

