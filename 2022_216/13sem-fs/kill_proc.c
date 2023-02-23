#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    // Выделяем 2 гб памяти
    size_t size = 2ULL * 1024 * 1024 * 1024;

    // Видим, что физической памяти выделилось сильно меньше, чем виртуальной
    // cat /proc/<pid>/status - VmSize - сколько выделилось виртуальной памяти,
    // VmRss - сколько физической
    char* ptr = malloc(size);
    if (!ptr) {
        perror("[malloc]");
        exit(1);
    }

    // Просто пауза, которую мы можем прервать введя символ
    getchar();


    // есть запустим с аргументом командной строки, то тогда память
    // будет заполняться единицами и ее придется физически выделять.
    // Можно в htop посмотреть на свободную память и размер swap файла
    if (argc > 1) {
        memset(ptr, '1', size);
        printf("success\n");
        getchar();
    }

}
