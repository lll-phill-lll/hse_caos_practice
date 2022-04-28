#include <stdio.h>
#include <sys/time.h>
#include <sys/time.h>


int main() {
    struct timeval current_time; // struct timeval хранит секунды и микросекунды
    gettimeofday(&current_time, NULL); // gettimeofday почти как time, но дает более высокую точность
    // accuracy: 20ms
    printf("sec: %ld, usec: %ld\n", current_time.tv_sec, current_time.tv_usec);
}
