#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"

#define MAX_CMD_LEN 1024

int execute_command(ParsedInput *parsed) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(parsed->commands[0].args[0], parsed->commands[0].args);
        perror("exec");
        _exit(1);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return 1;
}

int main() {
    char cmd[MAX_CMD_LEN];

    while (1) {
        printf("\033[1;33mEnter command\033[0m$ ");

        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = '\0';

        ParsedInput parsed;
        parse_input(cmd, &parsed);
        // print_parsed(&parsed);

        if (execute_command(&parsed)) {
           printf("!! Non zero exit status !!\n");
        }
    }
}
