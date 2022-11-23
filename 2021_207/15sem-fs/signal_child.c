#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

volatile int flag = 0;

void handler(int n) {
    const char msg[] = "Got signal\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

void child_handler(int n, siginfo_t* siginf, void *unused) {
    // don't use printf
    printf("Child killed. pid: %d, signal: %d\n", siginf->si_pid, n);
}

int main() {

    sigaction(SIGUSR1,
               &(struct sigaction){ .sa_handler = handler,
                                    .sa_flags = SA_RESTART }, NULL);
    int pid = fork();
    if (!pid) {
        printf("parent_pid: %d, child_pid: %d\n", getppid(), getpid());
        sleep(20);
        _exit(0);
    }

    // sigaction(SIGCHLD,
    //            &(struct sigaction){ .sa_sigaction = child_handler,
    //                                 .sa_flags = SA_RESTART | SA_SIGINFO }, NULL);
    sleep(20);

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("");
        exit(1);
    }

    if (WIFEXITED(status)) {
        printf("Exit status: %d\n", WEXITSTATUS(status));
    }

    if (WIFSIGNALED(status)) {
        printf("Exit signal: %d\n", WTERMSIG(status));
    }

}
