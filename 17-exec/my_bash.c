#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_CMD_LEN 1024

int main() {
    char cmd[MAX_CMD_LEN];

    while (1) {
        printf("\033[1;33mEnter command\033[0m$ ");

        scanf("%1023s", cmd);

        pid_t pid = fork();
        if (pid == 0) {
            execlp(cmd, cmd, NULL);
            perror("exec");
            _exit(1);
        }

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                printf("Non zero exit status\n");
            }
        }
    }
}
