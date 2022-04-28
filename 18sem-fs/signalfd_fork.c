#include <unistd.h>
#include <stdio.h>
#include <sys/signalfd.h>
#include <sys/wait.h>
#include <sys/types.h>

void do_some_large_task() {
    pid_t my_pid = getpid();

    printf("[CHILD] %d: started task\n", my_pid);

    sleep(my_pid % 5);

    printf("[CHILD] %d: finished task\n", my_pid);
}

void child_action() {

    do_some_large_task();

    kill(getppid(), SIGUSR1);
    _exit(0);
}

int main() {
    const int child_num = 5;

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);

    // No SIGKILL SIGSTOP
    sigprocmask(SIG_BLOCK, &mask, NULL);

    for (int i = 0; i != child_num; ++i) {
        pid_t pid = fork();
        // if we are child
        if (!pid) {
            child_action();
        }
    }

    // what if we move sigprocmask here?

    int sfd = signalfd(-1, &mask, 0);

    struct signalfd_siginfo fdsi;
    int child_count = 0;
    while (child_count < child_num) {
        // sleep(5);
        read(sfd, &fdsi, sizeof(struct signalfd_siginfo));

        if (fdsi.ssi_signo == SIGUSR1) {
            printf("Got SIGINT from %u\n", fdsi.ssi_pid);
            child_count++;
        }
    }

    printf("[PARENT] all children finished tasks\n");

    // do some logic

    for (int i = 0; i != child_num; ++i) {
        wait(NULL);
    }
}
