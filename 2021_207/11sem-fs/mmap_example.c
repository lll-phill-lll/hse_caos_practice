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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "expected filename\n");
        exit(1);
    }
    char* filename = argv[1];
    char c = 'c';

    // Открываем с правами на чтение и запись,
    // чтение - смапить в виртуальную память,
    // запись - записать обратно измененный файл
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("can't open");
        exit(1);
    }

    struct stat st;
    // Используем fstat для получения
    // данных о файле через файловый дескриптор
    if (fstat(fd, &st) == -1) {
        perror("can't stat");
        exit(1);
    }

    int input_size = st.st_size;
    // Нам не важно, куда смапится файл, поэтому первый параметр NULL
    // размер памяти = размер файла
    // В качестве 3 аргумента вообще можно передать и просто PROT_WITE потому что часто "Note that, due to hardware limitations, on some platforms PROT_WRITE may imply PROT_READ" назначение read прав следует из назначения write.
    // MAP_SHARED тут необходим, потому что если использовать MAP_PRIVATE, то при изменении файл не сохранится обратно в операционную систему
    // наш файловый дескриптор
    // хотим читать файл с самого начала, поэтому offset = 0
    void *mp = mmap(NULL, input_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    // В случае ошибки нужно проверять на MAP_FAILED
    // не на NULL. И после этого уже кастовать в нужный тип
    if (mp == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }

    char* data = mp;

    printf("File: %s", data);
    for (int i = 0; i != input_size; ++i) {
        data[i] = c;
    }

    // При желании можно сделать msync и принудительно записать
    // изменения обратно в файл
    // Но при вызове munmap это тоже произойдет

    if (munmap(mp, input_size) == -1) {
        perror("error");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("error");
        exit(1);
    }

    return 0;
}
