#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();

    printf("%d\n", pid);
    pid_t my_pid = getpid();
    printf("my pid: %d\n", my_pid);

    printf("hello world\n");

    if (pid != 0) {
        waitpid(pid, NULL, 0);
    }

    return 0;
}
