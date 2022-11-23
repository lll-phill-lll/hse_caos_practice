#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

void do_some_large_task() {
    pid_t my_pid = getpid();

    printf("[CHILD] %d: started task\n", my_pid);

    sleep(my_pid % 5);

    printf("[CHILD] %d: finished task\n", my_pid);
}

void child_action(int fds[]) {
    close(fds[0]);

    do_some_large_task();

    int done = 1;
    write(fds[1], &done, sizeof(done));

    // so something
    _exit(0);
}

int main() {
    const int child_num = 5;

    int fds[2];
    pipe(fds);

    for (int i = 0; i != child_num; ++i) {
        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action(fds);
        }
    }

    int done;
    // for (int i = 0; i != child_num; ++i) {
    //     read(fds[0], &done, sizeof(done));
    // }

    close(fds[1]);
    while (read(fds[0], &done, sizeof(done)));

    printf("[PARENT] all children finished tasks\n");

    // do some logic

    for (int i = 0; i != child_num; ++i) {
        wait(NULL);
    }
}
