#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("hello");

    if (fork() == 0) {

        _exit(0);
        // exit(0);
    };

    sleep(1);

    return 0;
}
