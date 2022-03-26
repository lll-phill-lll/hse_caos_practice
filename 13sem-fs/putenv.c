#include <stdio.h>
#include <stdlib.h>

void print_env(const char* env_name) {  // по прежнему печатает значение переменной окружения
    char* env = getenv(env_name);
    if (!env) {
        printf("not found\n");
    } else {
        printf("%s\n", env);
    }
}

int main() {
    print_env("HELLO");
    
    putenv("HELLO=not world");    // заменяет значение переменной окружения HELLO на not world
    print_env("HELLO");

    
    putenv("HELLO=");             // заменяет значение переменной окружения HELLO на \0
    print_env("HELLO");

    
    putenv("HELLO");              // указали переменную окружения без равно, поэтому переменная
                                  // окружения удаляется в рамках нашей программы. и вывод - not found
    print_env("HELLO");
}
