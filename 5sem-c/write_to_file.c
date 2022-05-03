#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum {
    BUF_SIZE = 8
};


int main(int argc, char* argv[]) {
    // argv[0] = "./a.out"
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }

    int fd = open(argv[1], O_WRONLY/*пишем*/|O_CREAT/*создаем*/|O_APPEND/*дописываем*/, S_IRUSR|S_IWUSR);
    // Если удалось открыть корректно, то файловый дескриптор больше нуля
    if (fd < 0) {
        fprintf(stderr, "failed open file\n");
        exit(1);
    }

    char buf[BUF_SIZE];

    ssize_t input_size;
    // Сколько запросили и сколько считали — разные числа
    while ((input_size = read(STDIN_FILENO, buf, BUF_SIZE)) != 0) {
        if (input_size < 0) {
            fprintf(stderr, "failed read\n");
            exit(1);
        }

        // think about small write
        ssize_t output_size = write(fd, buf, input_size);
        if (output_size != input_size) {
            fprintf(stderr, "failed write\n");
            exit(1);
        }
    }

    // Обязательно закрываем файловый дескриптор
    int close_res = close(fd);
    if (close_res == -1) {
        fprintf(stderr, "failed write\n");
        exit(1);
    }

    return 0;
}
