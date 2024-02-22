#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void child_function() {
    printf("[child] my pid = %d\n", getpid());
    sleep(10);
    _exit(0);
}

int main() {
    pid_t pid;
    if ((pid = fork()) == 0) {
        child_function();
    };

    while (1) {
        int res = waitpid(pid, NULL, WNOHANG);
        if (res == -1) {
            perror("");
            exit(1);

        } else if (res == 0) {
            // so something useful
            printf("[parent] waiting 1 sec\n");
            sleep(1);
        } else {
            printf("[parent] child finished\n");
            break;
        }
    }

    return 0;
}
