#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// fork + exec
int main() {
    pid_t pid = fork(); // создаем ребенка
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (!pid) {  // тело ребенка заменяем другим процессом, который хотим выполнить
        execl("/usr/bin/echo", "echo", "hello world", NULL);   // выведет hello world
        // execl("/usr/bin/sleep", "echo", "100", NULL);
        perror("exec");
        _exit(1);
    }
    
    // в родители продолжаем свои делишки
    int status;
    if (waitpid(pid, &status, 0) == -1) {  // ждем выполнения ребенка
        perror("waitpid");
        exit(1);
    }
    
    if (WIFEXITED(status)) {  // смотрим на статус ребенка
        printf("Exit status: %d\n", WEXITSTATUS(status));     // status = 0
    }
    return 0;
}
