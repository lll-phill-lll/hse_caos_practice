/*
 * Хотим сделать так, чтобы и ребенок и родитель имели доступ к одной и той же переменной
 *
 */

// fork
#include <unistd.h>
// mmap
#include <sys/mman.h>
// wait
#include <sys/wait.h>
// printf
#include <stdio.h>

int main() {

    void* mp = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (mp == MAP_FAILED) {
        perror("mmap");

    }

    int *x = mp;
    *x = 1;

    if (fork() == 0) {
        printf("Child: %d\n", *x);
        *x = 100;
    } else {
        sleep(1);
        printf("Parent: %d\n", *x);
        *x = 500;
        wait(NULL);
    }
    return 0;
}
