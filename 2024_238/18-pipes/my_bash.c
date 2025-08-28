#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"

#define MAX_CMD_LEN 1024

int execute_all_commands(ParsedInput *parsed) {
    int pipes[parsed->count - 1][2];

    for (int i = 0; i < parsed->count; ++i) {
        if (i < parsed->count - 1) pipe(pipes[i]);
        
        pid_t pid = fork();

        if (pid == 0) {
            Command cmd = parsed->commands[i];
            if (i == 0 && cmd.input) {
                int fd = open(cmd.input, O_RDONLY);
                dup2(fd, 0);
                close(fd);
            }

            if (i == parsed->count - 1 && cmd.output) {
                int fd;
                if (cmd.append) {
                    fd = open(cmd.output, O_RDWR |O_APPEND);
                } else {
                    fd = open(cmd.output, O_RDWR | O_TRUNC);
                }
                dup2(fd, 1);
                close(fd);
            }

            if (i == parsed->count - 1 && cmd.error) {
                int fd;
                fd = open(cmd.error, O_RDWR | O_TRUNC);
                dup2(fd, 2);
                close(fd);
            }

            if (i > 0) {
                dup2(pipes[i - 1][0], 0);
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
            }

            if (i < parsed->count - 1) {
                dup2(pipes[i][1], 1);
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            execvp(cmd.args[0], cmd.args);
            perror("exec");
            _exit(1);
        }

        if (i > 0) {
            close(pipes[i - 1][0]);
            close(pipes[i - 1][1]);
        }
    }

    for (int i = 0; i < parsed->count; ++i) {
        wait(NULL);
    }
    return 0;
}

int execute_command(ParsedInput *parsed) {
    pid_t pid = fork();
    if (pid == 0) {
        Command cmd = parsed->commands[0];
        if (cmd.input) {
            int fd = open(cmd.input, O_RDONLY);
            dup2(fd, 0);
            close(fd);
        }

        if (cmd.output) {
            int fd;
            if (cmd.append) {
                fd = open(cmd.output, O_RDWR |O_APPEND);
            } else {
                fd = open(cmd.output, O_RDWR | O_TRUNC);
            }
            dup2(fd, 1);
            close(fd);
        }

        if (cmd.error) {
            int fd;
            fd = open(cmd.error, O_RDWR | O_TRUNC);
            dup2(fd, 2);
            close(fd);
        }
        execvp(cmd.args[0], cmd.args);
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
        print_parsed(&parsed);

        if (execute_all_commands(&parsed)) {
           printf("!! Non zero exit status !!\n");
        }
    }
}
