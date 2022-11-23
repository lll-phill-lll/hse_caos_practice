#include <stdio.h>
#include <unistd.h>
#include <signal.h>
//                      про atomic:
// атомарные типы гарантируют, что операция или завершится или вообще не выполнится и эти
// переменные можно безопасно менять как и в hendler так и в main, и не бояться, что что-то попортиться

// volatile  для того, чтобы не было оптимизации, (программа зохочет оптимизировать cnt,
// так как увидит, что изменяется cnt только один разб НО handler вызывается ассинхронно)

volatile sig_atomic_t cnt = 0;
volatile sig_atomic_t flag = 0;

void sigint_handler(int n) {
    flag = 1;
    if (++cnt == 3) {     // на третий ^C выходит из программы (два первых раза игнорит ^C)
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
