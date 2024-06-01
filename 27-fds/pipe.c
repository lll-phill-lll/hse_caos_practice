#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

#define CHILD_NUM 5

void do_some_large_task() {
    pid_t my_pid = getpid();

    printf("[%d]: started task\n", my_pid % CHILD_NUM);

    sleep(my_pid % 5);

    printf("[%d]: finished task\n", my_pid % CHILD_NUM);
}

void child_action(int fds[]) {
    close(fds[0]);

    do_some_large_task();

    // notify parent that large task is done
    int done = 1;
    write(fds[1], &done, sizeof(done));
    close(fds[1]);

    // do something
    _exit(0);
}

int main() {
    int fds[2];
    pipe(fds);

    for (int i = 0; i != CHILD_NUM; ++i) {
        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(fds);
        }
    }

    int done;
    close(fds[1]);
    while(read(fds[0], &done, sizeof(done)));

    printf("[PARENT] all children finished tasks\n");

    // do some logic

    for (int i = 0; i != CHILD_NUM; ++i) {
        wait(NULL);
    }
}
