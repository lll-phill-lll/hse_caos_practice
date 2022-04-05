#include <time.h>
#include <stdio.h>

void print_tm(struct tm timeinfo) {
    printf("tm_sec:   %d\n"
           "tm_min:   %d\n"
           "tm_hour:  %d\n"
           "tm_mday:  %d\n"
           "tm_mon:   %d\n"
           "tm_year:  %d\n"
           "tm_wday:  %d\n"
           "tm_yday:  %d\n"
           "tm_isdst: %d\n",
           timeinfo.tm_sec,
           timeinfo.tm_min,
           timeinfo.tm_hour,
           timeinfo.tm_mday,
           timeinfo.tm_mon,
           timeinfo.tm_year,
           timeinfo.tm_wday,
           timeinfo.tm_yday,
           timeinfo.tm_isdst);
}

int main() {
    time_t t = time(NULL);
    printf("%lu\n", t);

    struct tm* timeinfo;

    timeinfo = localtime(&t);

    timeinfo->tm_hour += 100;
    print_tm(*timeinfo);
    printf("--------\n");

    mktime(timeinfo);

    print_tm(*timeinfo);
    printf("--------\n");
}
