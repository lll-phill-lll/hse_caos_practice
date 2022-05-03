#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

const char* filename = "sometmp.txt";

void write_to_file(pid_t pid) {
    char perror_str[20];

    sprintf(perror_str, "Pid: %d", pid);

    int fd = open(filename, O_WRONLY|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd == -1) {
        perror(perror_str);
        return;
    }


    const char* hello = "hello\n";
    ssize_t output_size = write(fd, hello, strlen(hello));
    if (output_size != strlen(hello)) {
        perror(perror_str);
        return;
    }

    // Закрываем файл всегда после выхода
    if (close(fd) == -1) {
        perror(perror_str);
        return;
    }

    printf("Pid: %d written successfully\n", pid);
}

void delete_file() {
    int status = remove(filename);
    if (status == -1) {
        perror("delete");
        return;
    }
    printf("file deleted\n");
}

int main() {

    // указанная функция вызыва­ется в конце выполнения программы
    atexit(delete_file);

    pid_t parent_pid = getpid();
    printf("Parent pid: %d\n", getpid());

    write_to_file(parent_pid);

    if (fork() == 0) {
        pid_t child_pid = getpid();
        printf("Child pid: %d\n", child_pid);
        // Вообще мы открываем файл, здороваемся с миром в этом файле, 
        // если не удалось, печатаем ошибку, иначе говорим, что всё хорошо
        // и печатаем ID процесса, который ее вызвал. 
        // При каждом вызове функции будем открывать и закрывать файл.
        write_to_file(child_pid);
        sleep(2);
        _exit(0); // ВЫВОД В РИДМИ
    }

    wait(NULL); // ждет любого ребенка

    write_to_file(parent_pid);

    return 0;
}
