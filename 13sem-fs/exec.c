#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char* argv[]) {
    // int status = execl("/usr/bin/echo", "echo", "hello world", NULL);

    // int status = execlp("echo", "echo", "hello world", NULL);

    // char* params[] = {"echo", "hello world", NULL};
    // int status = execvp("echo", params);

    // char* envs[] = {"PWD=hello", NULL};
    // int status = execle("/usr/bin/printenv", "printenv", "PWD", NULL, environ);

    // char* cmd = "ls -la";
    // int status = execl("/bin/sh", "sh", "-c", cmd, NULL);

    char* cmd = "echo -e \"${RED}hello${NC} world\"";
    setenv("RED", "\033[0;31m", 1);
    setenv("NC", "\033[0m", 1);
    int status = execl("/bin/bash", "sh", "-c", cmd, NULL);
    // no need
}
