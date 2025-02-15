#include <stdio.h>
#include <unistd.h>

int main() {
    printf("hello world!");

    fork();
    _exit(0);
}
