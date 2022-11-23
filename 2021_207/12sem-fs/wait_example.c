#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    pid_t pid = fork();
    if (pid == 0) {
        printf("child pid = %d\n", getpid());
        sleep(50);
        printf("hello world\n");
        _exit(5);
    };

    int status;
    // в статус записывается то, как именно завершился ребенок
    if (waitpid(pid, &status, 0) == -1) {
        perror("");
        exit(1);
    }

    i// Проверка того, завершился ли ребенок
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
