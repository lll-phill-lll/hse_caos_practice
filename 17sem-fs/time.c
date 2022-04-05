#include <time.h>
#include <stdio.h>

int main() {
    time_t t = time(NULL);
    printf("%lu\n", t);

    printf("year: %ld\n", t / 3600 / 24 / 365 + 1970);

    printf("hour: %ld\n", t / 3600 % 24);
}
