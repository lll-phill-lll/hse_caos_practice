#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main() {
    pid_t p = getpid();
    printf("%u\n", p);
    sleep(10);

    while (1) {
       malloc(0);
    }
}
