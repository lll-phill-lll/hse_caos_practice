#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // getenv(str) - принимает строчку и возвращает указатель на память, где лежит значение переменной окружения,
    // если такой переменно нет, getenv() возвращает NULL.
    // в argv[1] передается имя программы.
    char* env = getenv(argv[1]);
    if (!env) {
        printf("not found\n");
    } else {
        printf("%s\n", env);
    }
}
