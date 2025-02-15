#include "stdio.h"
#include "unistd.h"

int main() {
    printf("Process Id (pid): %d\n", getpid());
    printf("Parent Pid: %d\n", getppid());
    sleep(1000);
}
