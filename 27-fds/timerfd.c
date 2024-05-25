#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void disarm_timer(int tfd) {
    struct itimerspec stop_value;
    stop_value.it_value.tv_sec = 0;
    stop_value.it_value.tv_nsec = 0;
    stop_value.it_interval.tv_sec = 0;
    stop_value.it_interval.tv_nsec = 0;

    timerfd_settime(tfd, 0, &stop_value, NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "not enough args\n");
        exit(1);
    }

   // struct timespec now;
   // clock_gettime(CLOCK_REALTIME, &now);

   int fd = timerfd_create(CLOCK_REALTIME, 0);

   struct itimerspec new_value;
   new_value.it_value.tv_sec = atoi(argv[1]);
   new_value.it_value.tv_nsec = 0;
   //
   new_value.it_interval.tv_sec = atoi(argv[2]);
   new_value.it_interval.tv_nsec = 0;


   timerfd_settime(fd, 0, &new_value, NULL);

   printf("timer started\n");

   uint64_t exp;
   const int max_alarms = 50;
   int alarms = 0;
   while (1) {
       if (alarms >= max_alarms) {
           disarm_timer(fd);
           break;
       }

       read(fd, &exp, sizeof(exp));

       printf("timer expired %lu times\n", exp);
       alarms++;
   }
}

