/*
 * Хотим проверить, изменится ли значение переменной в ребенке, если поменять ее в родителе (или наоборот)
 *
 */

// printf
#include <stdio.h>
// fork
#include <unistd.h>
// wait
#include <sys/wait.h>

int main() {
    int x = 1;

    if (fork() == 0) {
        sleep(1);
        printf("Child: %d\n", x);
        x = 100;
    } else {
        printf("Parent: %d\n", x);
        x = 500;
        wait(NULL);
    }
    return 0;
}
