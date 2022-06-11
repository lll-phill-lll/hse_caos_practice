#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGUSR1);

    // No SIGKILL SIGSTOP
    sigprocmask(SIG_BLOCK, &mask, NULL);

    int sfd = signalfd(-1, &mask, 0);

    struct signalfd_siginfo fdsi;
    while (1) {
        read(sfd, &fdsi, sizeof(struct signalfd_siginfo));

        if (fdsi.ssi_signo == SIGINT) {
            printf("Got SIGINT from %u\n", fdsi.ssi_pid);
        } else if (fdsi.ssi_signo == SIGQUIT) {
            printf("Got SIGQUIT from %u\n", fdsi.ssi_pid);
            exit(EXIT_SUCCESS);
        } else {
            printf("Read unexpected signal\n");
        }
    }
}

