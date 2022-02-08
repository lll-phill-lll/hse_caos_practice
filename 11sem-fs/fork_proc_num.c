#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n = 4;

    for (int i = 0; i < n; i++) {
        fork();
    }

    printf("%d\n", getpid());

    int status;
    pid_t ch_pid;
    while ((ch_pid = wait(&status)) > 0);

    return 0;
}



