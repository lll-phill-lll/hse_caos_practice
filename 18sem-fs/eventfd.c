#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/wait.h>

uint64_t do_some_large_task() {
    pid_t my_pid = getpid();

    // printf("[CHILD] %d: started task\n", my_pid);

    sleep(my_pid % 5);

    uint64_t computed = (my_pid % 5) * 3 + 2;
    printf("[CHILD] %d: computed %lu\n", my_pid, computed);

    // printf("[CHILD] %d: finished task\n", my_pid);

    return computed;
}

void child_action(int efd) {

    uint64_t computed = do_some_large_task();
    write(efd, &computed, sizeof(computed));

    // do some logic

    _exit(0);
}

int main() {
    int efd = eventfd(0, 0);

    const int child_num = 5;

    for (int i = 0; i != child_num; ++i) {
        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(efd);
        }
    }

    const int retries = 3;
    int retry = 0;
    uint64_t res;
    uint64_t res_sum = 0;
    while (retry < retries) {
        sleep(1);
        read(efd, &res, sizeof(res));
        printf("[PARENT] read: %lu\n", res);
        res_sum += res;

        retry++;
    }

    printf("[PARENT] total read: %lu\n", res_sum);

    for (int i = 0; i != child_num; ++i) {
        wait(NULL);
    }
}


