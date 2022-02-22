#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* env = getenv(argv[1]);
    if (!env) {
        printf("not found\n");
    } else {
        printf("%s\n", env);
    }

}
