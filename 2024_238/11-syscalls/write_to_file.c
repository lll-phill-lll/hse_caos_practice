#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum { BUF_SIZE = 1024 };

int main(int argc, char* argv[]) {
    // argv[0] = "./a.out"
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }

    int fd =
        open(argv[1],
             O_WRONLY /*пишем*/ | O_CREAT /*создаем*/ | O_APPEND /*дописываем*/,
             S_IRUSR | S_IWUSR);

    // Если удалось открыть корректно, то файловый дескриптор больше нуля

    char buf[BUF_SIZE];

    ssize_t input_size;
    // Сколько запросили и сколько считали — разные числа
    while ((input_size = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {

        // think about small write
        ssize_t output_size = write(fd, buf, input_size);
    }

    // Обязательно закрываем файловый дескриптор
    close(fd);

    return 0;
}
