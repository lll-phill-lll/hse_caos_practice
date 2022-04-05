#include <stdio.h>
#include <sys/time.h>
#include <sys/time.h>


int main() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    // accuracy: 20ms
    printf("sec: %ld, usec: %ld\n", current_time.tv_sec, current_time.tv_usec);
}
