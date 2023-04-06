#include <stdio.h>
#include <sys/time.h>
#include <sys/time.h>


int main() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("sec: %ld, usec: %ld\n", current_time.tv_sec, current_time.tv_usec);

    struct timeval current_time2;
    gettimeofday(&current_time2, NULL);

    printf("%ld\n", current_time2.tv_usec - current_time.tv_usec);
}
