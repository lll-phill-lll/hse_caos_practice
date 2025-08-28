#include <stdio.h>
#include <unistd.h>

int main() {
    printf("I'm printed once\n");

    pid_t pid = fork();

    printf("I'm printed twice\n");

    if (pid == 0) {
        printf("Child\n");
    } else if (pid > 0) {
        printf("Parent\n");
    }

    while (1) {
        printf("[%d] pid returned after fork: %d, parent pid: %d\n", getpid(),
               pid, getppid());
        sleep(100);
    }
}
