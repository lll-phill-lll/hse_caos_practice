#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void handler(int n) {
    const char msg[] = "Ctrl-C pressed\n";
    write(STDOUT_FILENO, msg, sizeof(msg)-1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = SA_NODEFER;
    sigaction(SIGINT, &sa, NULL);

    sigset_t mask;            // выделяем маску
    sigemptyset(&mask);       // очищаем ее
    sigaddset(&mask, SIGINT); // заполняем маску SIGINTом

    // есть кусок кода, где важно, чтобы никакой сигнал не влез и не помешал исполнению

    while (1) {
        sigprocmask(SIG_BLOCK, &mask, NULL);   // передаем маску сигнала, которую мы хотим отложить
        /*--------dont touch me---------------*/
        printf("sleep started\n");
        sleep(10);
        printf("sleep ended\n");
        /*------------------------------------*/
        sigprocmask(SIG_UNBLOCK, &mask, NULL);  // если сигнал какой-то и был, то даст о себе знать он только здесь
    }
}
