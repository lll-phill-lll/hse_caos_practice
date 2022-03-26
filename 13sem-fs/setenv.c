#include <stdio.h>
#include <stdlib.h>

void print_env(const char* env_name) {
    char* env = getenv(env_name);
    if (!env) {
        printf("%s: not found\n", env_name);
    } else {
        printf("%s: %s\n", env_name, env);
    }
}

int main() {

    // setenv(имя, значение, [флаг, в случае, если уже существует переменная])
    int status;
    print_env("HELLO2");
    // создаем новую переменную окружения HELLO2, записываем туда not world и
    // флаг 0 запрещает нам переписывать новое значение, если HELLO2 уже существует.
    status = setenv("HELLO2", "not world", 0);
    printf("setenv status: %d\n", status);
    print_env("HELLO2");

    printf("-------\n");

    print_env("HELLO"); // уже существующая переменная окружения
    // хотим перезаписать, но т.к. 0 - не получилось, там все так же лежит world, ноооо важно! status у
    // нас от этого не портится, он так же равен 0, значит ничвего не ломается, просто не перезаписывается.
    status = setenv("HELLO", "not world", 0);
    printf("setenv status: %d\n", status);
    print_env("HELLO");  // выведет HELLO = world

    printf("-------\n");

    print_env("HELLO");
    status = setenv("HELLO", "not world", 1); // flag != 0 разрешает перезаписывать
    printf("setenv status: %d\n", status);      // status по прежнему 0
    print_env("HELLO");               // выведет HELLO = not world

    printf("-------\n");

    print_env("HELLO");
    status = setenv("HELLO", "", 1);    // положили пустую строку, все легально, перезаписалось
    printf("setenv status: %d\n", status);
    print_env("HELLO");

    printf("-------\n");

    print_env("HELLO");
    status = setenv(NULL, "", 1);
    printf("setenv status: %d\n", status);     // status = 1 --> произошла ошибка
    print_env("HELLO");

    printf("-------\n");

    print_env("HELLO");
    unsetenv("HELLO");            // функция для удаления переменной окрежения
    print_env("HELLO");  // not found
}
