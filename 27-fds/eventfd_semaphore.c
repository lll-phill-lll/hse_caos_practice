#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/wait.h>


#define CHILD_NUM 5

void do_some_large_task(int my_num) {
    printf("[%d]: started task\n", my_num);

    sleep(my_num + 1);

    printf("[%d]: finished task\n", my_num);
}

void child_action(int efd) {
    pid_t my_pid = getpid();
    uint64_t res;

    while(1) {
        printf("[%d]: is waiting for the task\n", my_pid % CHILD_NUM);
        read(efd, &res, sizeof(res));
        do_some_large_task(my_pid % CHILD_NUM);
    }

    _exit(0);
}

int main() {
    int efd = eventfd(0, EFD_SEMAPHORE);

    for (int i = 0; i != CHILD_NUM; ++i) {
        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(efd);
        }
    }

    while (1) {
        uint64_t count = 0;
        scanf("%lu", &count);
        write(efd, &count, sizeof(count));
    }

    printf("[PARENT] all children finished tasks\n");

    for (int i = 0; i != CHILD_NUM; ++i) {
        wait(NULL);
    }
}


