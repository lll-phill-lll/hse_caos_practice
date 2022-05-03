#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    pid_t pid;
    if ((pid = fork()) == 0) {
        printf("child pid = %d\n", getpid());
        sleep(10);
        _exit(0);
    };

    while (1) {
        int res = waitpid(pid, NULL, WNOHANG /*не ждать, если не завершился процесс*/);
        if (res == -1) {
            perror("");
            exit(1);

        } else if (res == 0) {
            // so something useful
            printf("waiting 1 sec\n");
            sleep(1);
        } else {
            printf("child finished\n"); // ВЫВОД В РИДМИ
            break;
        }
    }

    return 0;
}
