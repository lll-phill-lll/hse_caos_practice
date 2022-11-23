#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int n, siginfo_t* siginf, void *unused) {
    int  caller_pid = siginf->si_pid;

    // don't use printf
    printf("pid: %d", caller_pid);
}

int main() {
    struct sigaction sa = {};
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        printf("hello world!\n");
        sleep(1);
    }
}
