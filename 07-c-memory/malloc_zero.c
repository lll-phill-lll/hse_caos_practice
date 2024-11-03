#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main() {
    // Узнаем pid процесса, чтобы можно было проследить за выделяемой памятью
    pid_t p = getpid();
    printf("%u\n", p);
    // спим немного, чтобы можно было подготовить окружение и наблюдать за реакцией
    sleep(10);

    while (1) {
       malloc(0);
    }
}
