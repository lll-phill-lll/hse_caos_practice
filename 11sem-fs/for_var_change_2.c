#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    void* mp = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    int *x = mp;
    *x = 1;

    if (fork() == 0) {
        printf("Child: %d\n", *x);
        *x = 100;
    } else {
        sleep(1);
        printf("Parent: %d\n", *x);
        *x = 500;
    }
    wait(NULL);
    return 0;
}
