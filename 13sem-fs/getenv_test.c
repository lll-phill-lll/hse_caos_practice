#include <stdio.h>
#include <stdlib.h>

// попробуем изменить переменные окрыжения

void print_env(const char* env_name) {  // функция печатает переменную окружения
    char* env = getenv(env_name);
    if (!env) {
        printf("not found\n");
    } else {
        printf("%s\n", env);
    }
}

int main(int argc, char* argv[]) {

    print_env(argv[1]);      // печатаем олда

    char* env = getenv(argv[1]);      // откапываем переменную окружения
    env[0] = 'A';                     // меняем переменную окружения

    print_env(argv[1]);      // печатает измененную переменную окружения
}

// например, old -- world, а после модификации new -- Aorld, и если несколько раз изменить,
// то вообще указатель попортиться может, а кому это надо?

