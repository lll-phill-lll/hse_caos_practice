#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    int x = 1;

    if (fork() == 0) {
        printf("Child: %d\n", x);
        x = 100;
    } else {
        printf("Parent: %d\n", x);
        x = 500;
    }
    return 0;
}
