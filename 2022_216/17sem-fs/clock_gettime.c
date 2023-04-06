#include <time.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct timespec ts;
    // с помощью clock_gettime мы получаем более точное время
    // clock_gettime(CLOCK_REALTIME, &ts);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);

    printf("sec: %ld, nsec: %ld\n", ts.tv_sec, ts.tv_nsec);

    char* ctime_res = ctime(&ts.tv_sec);
    printf("time: %s", ctime_res);
}
