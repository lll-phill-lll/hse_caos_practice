#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t cnt = 0;
volatile sig_atomic_t flag = 0;

void sigint_handler(int n) {
    flag = 1;
    if (++cnt == 3) {
        _exit(0);
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        if (flag) {
            printf("Ctrl-C pressed\n");
            flag = 0;
        } else {
            printf("Some string to print\n");
        }
        sleep(1);
    }
    return 0;
}
