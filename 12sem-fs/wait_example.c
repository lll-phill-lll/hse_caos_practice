#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();
    if (pid == 0) {
        printf("child pid = %d\n", getpid());
        sleep(50);
        printf("hello world\n");
        _exit(5);
    };

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

    return 0;
}
