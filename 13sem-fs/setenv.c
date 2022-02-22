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

    int status;
    print_env("HELLO2");
    status = setenv("HELLO2", "not world", 0);
    printf("setenv status: %d\n", status);
    print_env("HELLO2");

    printf("-------\n");

    print_env("HELLO");
    status = setenv("HELLO", "not world", 0);
    printf("setenv status: %d\n", status);
    print_env("HELLO");

    printf("-------\n");

    print_env("HELLO");
    status = setenv("HELLO", "not world", 1);
    printf("setenv status: %d\n", status);
    print_env("HELLO");

    printf("-------\n");

    print_env("HELLO");
    status = setenv("HELLO", "", 1);
    printf("setenv status: %d\n", status);
    print_env("HELLO");

    printf("-------\n");

    print_env("HELLO");
    status = setenv(NULL, "", 1);
    printf("setenv status: %d\n", status);
    print_env("HELLO");

    printf("-------\n");

    print_env("HELLO");
    status = setenv("HELLO", "", 1);
    printf("setenv status: %d\n", status);
    print_env("HELLO");

    printf("-------\n");

    print_env("HELLO");
    unsetenv("HELLO");
    print_env("HELLO");
}
