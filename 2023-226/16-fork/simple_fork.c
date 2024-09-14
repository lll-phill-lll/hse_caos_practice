#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    while (1) {
        printf("[%d] pid returned after fork: %d, parent pid: %d\n", getpid(),
               pid, getppid());
        sleep(10);
    }
}
