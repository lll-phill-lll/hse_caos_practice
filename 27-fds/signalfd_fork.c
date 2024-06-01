#include <unistd.h>
#include <stdio.h>
#include <sys/signalfd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define CHILD_NUM 5

void do_some_large_task() {
    pid_t my_pid = getpid();

    printf("[%d]: started task\n", my_pid % CHILD_NUM);

    sleep(my_pid % CHILD_NUM);

    printf("[%d]: finished task\n", my_pid % CHILD_NUM);
}

void child_action() {

    do_some_large_task();

    kill(getppid(), SIGINT);
    _exit(0);
}

int main() {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    // No SIGKILL SIGSTOP
    sigprocmask(SIG_BLOCK, &mask, NULL);

    for (int i = 0; i != CHILD_NUM; ++i) {
        pid_t pid = fork();
        // if we are child
        if (!pid) {
            sigemptyset(&mask);
            sigprocmask(SIG_SETMASK, &mask, NULL);
            child_action();
        }
    }
    sleep(5);

    // what if we move sigprocmask here?

    int sfd = signalfd(-1, &mask, 0);

    struct signalfd_siginfo fdsi;
    int child_count = 0;
    while (child_count < CHILD_NUM) {
        // sleep(5);
        read(sfd, &fdsi, sizeof(struct signalfd_siginfo));

        if (fdsi.ssi_signo == SIGINT) {
            printf("[PARENT] Got SIGINT from %u\n", fdsi.ssi_pid % CHILD_NUM);
            child_count++;
        }
    }

    printf("[PARENT] all children finished tasks\n");

    // do some logic

    for (int i = 0; i != CHILD_NUM; ++i) {
        wait(NULL);
    }
}
