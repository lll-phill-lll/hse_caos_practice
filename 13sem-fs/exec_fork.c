#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (!pid) {
        execl("/usr/bin/echo", "echo", "hello world", NULL);
        // execl("/usr/bin/sleep", "echo", "100", NULL);
        perror("exec");
        _exit(1);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        exit(1);
    }

    if (WIFEXITED(status)) {
        printf("Exit status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
