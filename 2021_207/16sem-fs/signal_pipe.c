#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

volatile int do_write = 0;
volatile int max_num = 10;

void do_something(int *fd) {
    int num = 0;
    int neigh_pid;
    read(fd[0], &neigh_pid, sizeof(neigh_pid));
    int my_pid = getpid();

    printf("[%d] neigh: %d\n", my_pid, neigh_pid);

    pause();

    if (do_write) {
        printf("[%d] write\n", my_pid);
        write(fd[1], &num, sizeof(num));
        kill(neigh_pid, SIGUSR1);
        pause();
    }

    while(1) {
        read(fd[0], &num, sizeof(num));
        printf("[%d] %d\n", my_pid, num++);
        if (num == max_num) {
            kill(neigh_pid, SIGINT);
            _exit(0);
        }
        write(fd[1], &num, sizeof(num));
        kill(neigh_pid, SIGUSR1);
        pause();
    }
}

void start_func(int n) {
    do_write = 1;
}

void func(int _) {
}

int main() {
    sigaction(SIGUSR1,
               &(struct sigaction){ .sa_handler = func,
                                    .sa_flags = SA_RESTART }, NULL);

    sigaction(SIGUSR2,
               &(struct sigaction){ .sa_handler = start_func,
                                    .sa_flags = SA_RESTART }, NULL);
    int fd[2];
    pipe(fd);
    int pid1 = fork();
    // start child 1
    if (!pid1) {
        do_something(fd);
    }

    int pid2 = fork();
    if (!pid2) {
        do_something(fd);
    }
    printf("[%d] pid1: %d, pid2: %d\n", getpid(), pid1, pid2);

    write(fd[1], &pid1, sizeof(pid1));
    write(fd[1], &pid2, sizeof(pid2));

    wait(NULL);
    wait(NULL);
}
