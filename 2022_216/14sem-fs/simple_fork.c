// exit
#include <stdlib.h>
// printf
#include <stdio.h>
// fork, getpid
#include <unistd.h>
// waitpid
#include <sys/wait.h>
#include <sys/types.h>

int main() {

    pid_t pid = fork();

    printf("Fork's pid: %d\n", pid);
    pid_t my_pid = getpid();
    printf("My pid: %d\n", my_pid);

    printf("hello world\n");

    if (pid == 0) {
        printf("hello from child\n");
        sleep(100);
        exit(22);
    } else {
        int status;
        pid_t child_pid = waitpid(pid, &status, 0);
        if (child_pid == -1) {
            perror("error");
            exit(1);
        }
        if (WIFEXITED(status)) {
            printf("child exited normally: %d\n", WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status)) {
            printf("killed by signal: %d\n", WTERMSIG(status));
        }

        // waitpid(pid, NULL, 0);
    }

    return 0;
}
