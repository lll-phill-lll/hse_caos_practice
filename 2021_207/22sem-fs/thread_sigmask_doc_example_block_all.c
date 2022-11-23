#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void* sig_thread(void *arg) {
   sigset_t *s = arg;
   int sig;

   while (1) {
       sigwait(s, &sig);
       printf("Signal handling thread got signal %d\n", sig);
   }
}

int main() {
    sigset_t s;
    sigfillset(&s);
    pthread_sigmask(SIG_BLOCK, &s, NULL);

    pthread_t thread;
    pthread_create(&thread, NULL, &sig_thread, NULL);

    // pause main thread
    pause();
}
