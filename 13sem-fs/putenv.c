#include <stdio.h>
#include <stdlib.h>

void print_env(const char* env_name) {
    char* env = getenv(env_name);
    if (!env) {
        printf("not found\n");
    } else {
        printf("%s\n", env);
    }
}

int main() {

    print_env("HELLO");
    putenv("HELLO=not world");
    print_env("HELLO");

    putenv("HELLO=");
    print_env("HELLO");

    putenv("HELLO");
    print_env("HELLO");

}
