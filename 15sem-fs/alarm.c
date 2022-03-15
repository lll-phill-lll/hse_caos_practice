#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int n) {
    const char msg[] = "alarm!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(0);
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    sigaction(SIGALRM, &sa, NULL);

    alarm(3);

    while (1) {
        printf("hello world!\n");
        sleep(1);
    }
}
