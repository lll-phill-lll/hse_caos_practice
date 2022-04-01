#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

struct somedata {
    int a;
    int b;
    int c;
};

struct somedata sd;

void handler(int n) {
    char str[] = "[SIGNAL] a: xx, b: xx, c: xx\n";
    str[12] = sd.a / 10 + '0';
    str[13] = sd.a % 10 + '0';
    str[19] = sd.b / 10 + '0';
    str[20] = sd.b % 10 + '0';
    str[26] = sd.c / 10 + '0';
    str[27] = sd.c % 10 + '0';
    write(STDOUT_FILENO, str, sizeof(str) - 1);

    sd.a++;
    sleep(1);
    sd.b++;
    sleep(1);
    sd.c++;
}

int main() {
    struct sigaction sa = {};
    sa.sa_handler = handler;
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGUSR1, &sa, NULL);

    int counter = 1;

    while(1) {
        sleep(1);
        sd.a++;
        sleep(1);
        sd.b++;
        sleep(1);
        sd.c++;
        printf("[%d] a: %d, b: %d, c: %d\n", getpid(), sd.a, sd.b, sd.c);
    }
}
