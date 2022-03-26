#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {   // в envp[] хранятся переменные окружения
    while (*envp) {                                // выводятся все переменные окружения
        printf("%s\n", *envp++);
    }
}
