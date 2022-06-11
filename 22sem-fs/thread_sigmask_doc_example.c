#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void* sig_thread(void *arg) {
   sigset_t s;
   sigfillset(&s);
   int sig;

   while (1) {
       sigwait(s, &sig);
       printf("Signal handling thread got signal %d\n", sig);
       if (sigint == 2) {
           exit(0);
       }
   }
}

int main() {
    sigset_t s;
    sigemptyset(&s);
    // sigaddset(&s, SIGINT);
    sigfillset(&s);
    pthread_sigmask(SIG_BLOCK, &s, NULL);

    pthread_t thread;
    pthread_create(&thread, NULL, &sig_thread, (void *) &s);

    // pause main thread
    pause();
}
