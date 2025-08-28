#include <stdio.h>
#include <unistd.h>

int main() {
    int x = 100;

    pid_t pid = fork();
    if (pid == 0) {
        printf("[Child] x = %d\n", x);
        x = 1000;
        _exit(0);
    }

    sleep(10);

    printf("[Parent] x = %d\n", x);
    x = 500;
}
