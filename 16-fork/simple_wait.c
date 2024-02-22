#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void child_function() {
    printf("[child][%d] running\n", getpid());
    sleep(2);
    _exit(0);
}

int main() {
    int child_num = 5;

    for (int i = 0; i < child_num; ++i) {
        if (fork() == 0) {
            child_function();
        }
    }

    for (int i = 0; i < child_num; ++i) {
        wait(NULL);
    }

    printf("[parent] all processes finished\n");
}
