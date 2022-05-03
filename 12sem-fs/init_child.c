#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    pid_t pid;

    // возвращает идентификатор ID текущего процесса.
    printf("initial parent pid = %d\n", getpid());
    if ((pid = fork()) == 0) {
		for(int i = 0; i != 10; ++i) {
            // возвращает идентификатор ID родительского процесса. 
            printf("parent pid = %d\n", getppid());
            // Приостанавливает выполнение программы. Время задается в секундах.            
            sleep(1); 
        }
    }

    sleep(5);

    return 0;
}
