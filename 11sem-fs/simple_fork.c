// exit
#include <stdlib.h>
// printf
#include <stdio.h>
// fork, getpid
#include <unistd.h>
// waitpid
#include <sys/wait.h>
#include <sys/types.h>

int main() {

    // Создаем еще один процесс
    // Оба процесса продолжат выполнение со следующей инструкции после fork.
    // Чтобы отличить, в каком процессе мы находимся, нужно посмотреть на результат вызова fork: в ребенке он вернет 0, в родителе pid ребенка.
    pid_t pid = fork();

    // родитель напечатает pid ребенка, ребенок напечатает 0.
    // Но это не значит, что у ребенка pid=0.
    printf("%d\n", pid);
    // Функция вернет pid процесса. В этот раз и в ребенке и в родителе будет собственный pid
    pid_t my_pid = getpid();
    printf("my pid: %d\n", my_pid);

    // будет напечатано hello world 2 раза
    printf("hello world\n");

    // эта строчка вернет true для родителя и false для ребенка
    // Если хотим, чтобы в родителе и ребенке выполнялся разный код, то можно делать так
    if (pid != 0) {
        // Ждем, пока ребенок завершится и после этого уже завершаем выполнение родителя
        int status;
        //  вернет pid ребенка в случае успеха
        //  -1 в случае ошибки (и выставится errno)
        pid_t child_pid = waitpid(pid, &status, 0);
        if (child_pid == -1) {
            perror("error");
            exit(1);
        }
        // Проверяем, как завершился процесс.
        // man 2 waitpid
        if (WIFEXITED(status)) {
            printf("exited normally\n");
        }

        // Вместо status можно передать NULL, если статус нас не интересует и мы просто хотим дождаться завершения ребенка
        // waitpid(pid, NULL, 0);
    }

    return 0;
}
