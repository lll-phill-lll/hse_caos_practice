#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void* sig_thread(void *arg) {
   sigset_t s; // маска сигналов
   sigfillset(&s);
   int sig;

  /*
    Виснем, пока не пришел сигнал
  */
   while (1) {
       sigwait(s, &sig);
       printf("Signal handling thread got signal %d\n", sig);
       if (sigint == 2) {
           exit(0);
       }
   }
}

int main() {
    /*
      Блокируем все сигналы
    */
    sigset_t s;
    sigemptyset(&s);
    // sigaddset(&s, SIGINT);
    sigfillset(&s);
    pthread_sigmask(SIG_BLOCK, &s, NULL);

    pthread_t thread;
    /*
      Создаем специальный поток, который будет реагировать на сигналы
    */
    pthread_create(&thread, NULL, &sig_thread, (void *) &s);

    // pause main thread
    pause();
}
