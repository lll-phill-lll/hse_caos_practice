#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/wait.h>

void do_some_large_task() {
    pid_t my_pid = getpid();

    printf("[CHILD] %d: started task\n", my_pid);

    sleep(my_pid % 5);

    printf("[CHILD] %d: finished task\n", my_pid);
}

void child_action(int efd) {

    do_some_large_task();

    uint64_t done = 1;
    write(efd, &done, sizeof(done));

    // do some logic

    _exit(0);
}

int main() {
    int efd = eventfd(0, EFD_SEMAPHORE);

    const int child_num = 5;

    for (int i = 0; i != child_num; ++i) {
        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(efd);
        }
    }

    uint64_t done = -1;
    // for (int i = 0; i != child_num; ++i) {
    //     read(efd, &done, sizeof(done));
    //     printf("[PARENT] %lu\n", done);
    // }

    while (done) {
        read(efd, &done, sizeof(done));
        printf("[PARENT] %lu\n", done);
    }

    printf("[PARENT] all children finished tasks\n");

    for (int i = 0; i != child_num; ++i) {
        wait(NULL);
    }
}


