// example from https://github.com/blackav/hse-caos-2020/tree/master/16-exec
// пробуем симитировать запуск программы из shell ./program < file_in > file_out 2>> file_err
// она берет два числа, одно из них печатает в stdout, второе в stderr

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char stdin_filename[] = "file_in";     // находятся два числа
    char stdout_filename[] = "file_out";   // хотим одно число сюда
    char stderr_filename[] = "file_err";   // второе число сюда

    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    }

    if (!pid) {
        int fd = open(stdin_filename, O_RDONLY);  // создаем в ребенке
        if (fd < 0) {
            perror("in");
            _exit(1);
        }
        // скопировать файловый дескриптор fd в файловый дескриптор 0
        dup2(fd, 0);
        // fd больше не нужен и должен быть закрыт
        close(fd);

        // открыть файл в режиме перезаписи
        fd = open(stdout_filename, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if (fd < 0) {
            perror("out");
            _exit(1);
        }
        // скопировать файловый дескриптор fd в файловый дескриптор 1
        dup2(fd, 1);
        // fd больше не нужен и должен быть закрыт
        close(fd);

        // открыть файл в режиме добавления
        fd = open(stderr_filename, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        if (fd < 0) {
            perror("err");
            _exit(1);
        }
        dup2(fd, 2);
        close(fd);   // fd больше не нужен и должен быть закрыт

        execlp("./program", "./program", NULL);   // запускаем нашу программу
        _exit(1);
    }
    wait(NULL);
}
