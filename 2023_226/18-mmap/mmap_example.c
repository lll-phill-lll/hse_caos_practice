/*
 * Открыть файл и записать его в виртуальную память.
 * Заменить каждый символ на 'c' в этом файле
 * файл для теста - small_file.txt
 */

// printf
#include <stdio.h>
// exit
#include <stdlib.h>
// mmap, munmap
#include <sys/mman.h>
// fstat
#include <sys/stat.h>
// open
#include <fcntl.h>
// close
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }
    char* filename = argv[1];

    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("can't open");
        exit(1);
    }

    struct stat st;
    // Используем fstat для получения
    // данных о файле через файловый дескриптор
    // stat
    if (fstat(fd, &st) == -1) {
        perror("can't stat");
        exit(1);
    }

    int input_size = st.st_size;
    void* mp =
        mmap(NULL, input_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (mp == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("error");
        exit(1);
    }

    char* data = mp;

    printf("File before change: %s", data);
    for (int i = 0; i != input_size; ++i) {
        data[i] = '1';
    }

    if (munmap(mp, input_size) == -1) {
        perror("error");
        exit(1);
    }

    return 0;
}
