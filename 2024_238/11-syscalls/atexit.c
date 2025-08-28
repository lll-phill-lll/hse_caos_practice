#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bye() {
    printf("\nBye!\n");
}

int main() {
    atexit(bye);

    printf("hello from main\n");

    _exit(0);

}
