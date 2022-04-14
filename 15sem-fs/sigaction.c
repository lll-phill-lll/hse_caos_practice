#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int n) {
    char msg[] = "got signal\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s DELAY STRING\n", argv[0]);
        return 1;
    }
    struct sigaction sa = {};
    sa.sa_handler = handler;        // подкладываем вместо SIGINT -> handler
    // sa.sa_handler = SIG_IGN;     // подкладываем вместо SIGINT -> SIG_IGN (дефолтный хендлер-игнорщик)
    // sa.sa_handler = SIG_DFL;     // подкладываем вместо SIGINT -> SIG_DFL (еще один дефолтный хендлер)
    // sa.sa_flags = SA_RESTART;    // передаем флаг -> SA_RESTART (если сигнал поступил,
                                    // во время какого-то системного вызова, то после обработки сигнала системный вызов
                                    // рестартонется)
    sigaction(SIGINT, &sa, NULL);

    int delay = atoi(argv[1]);
    int counter = 1;

    while(1) {
        sleep(delay);  // при вызове SIGINT таймер sleep обнуляется
        printf("[%d] %d: %s\n", getpid(), counter++, argv[2]);
    }
}
