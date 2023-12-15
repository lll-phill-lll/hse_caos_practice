#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum {
    N = 5,
};

int main(int argc, char* argv[]) {
    int file = open(argv[1], O_RDONLY);  // хотим уметь только читать

    if (file == -1) {
        perror("lala");  // более осмысленная ошибка
        exit(1);
    }

    long x;
    sscanf(argv[2], "%ld", &x);
    long y;
    sscanf(argv[3], "%ld", &y);

    long offset = x * (N + 1) + y;

    // выставляет file pointer в нужное место
    if (lseek(file, offset, SEEK_SET) == -1) {
        perror("lseek");
        exit(1);
    }

    char c;
    if (read(file, &c, sizeof(char)) == -1) {
        perror("read");
        exit(1);
    }

    if (c == '1') {
        printf("Found\n");
    } else {
        printf("Try again\n");
    }

    close(file);
    return 0;
}
