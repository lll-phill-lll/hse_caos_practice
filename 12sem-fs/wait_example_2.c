#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    pid_t pid;
    if ((pid = fork()) == 0) {
        printf("child pid = %d\n", getpid());
        sleep(20);
        exit(1);
    };

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("");
        exit(1);
    }

    // Проверка того, завершился ли ребенок
    if (WIFEXITED(status)) {
        // Проверка статуса равершения
        printf("Exit status: %d\n", WEXITSTATUS(status));
    }
    // Проверка был ли убит ребенок 
    if (WIFSIGNALED(status)) {
        // Номер сигнала, при помощи которого убили (!!!)
        printf("Exit signal: %d\n", WTERMSIG(status));
    }

    return 0;
}
