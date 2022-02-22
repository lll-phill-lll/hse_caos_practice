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

int main(int argc, char* argv[]) {

    print_env(argv[1]);

    char* env = getenv(argv[1]);
    env[0] = 'A';

    print_env(argv[1]);
}
