/*
 *
 *
 *  С помощью fork посчитаем лимит на создаваемые пользователем процессы.
 *  Точнее, сколько еще процессов мы можем создать
 *
 *
 */

// fork, exit
#include <unistd.h>
// wait
#include <sys/wait.h>
// printf
#include <stdio.h>

int main() {
    // будем использовать счетчик с 1 (посчитали процесс родителя)
    int counter = 1;
    pid_t pid = 0;

    while (pid == 0) {
        // sleep(1);
        pid = fork();
        if (pid != -1) {
            counter++;
        } else {
            perror("error");
        }
    }

    if (pid > 0) {
        // каждый родитель ждет завершения своего ребенка
        waitpid(pid, NULL, 0);
    } else if (pid == -1) {
        // из самого последнего созданного ребенка напечатаем счетчик и завершимся
        printf("%d\n", counter);
        _exit(0);
    }

}
