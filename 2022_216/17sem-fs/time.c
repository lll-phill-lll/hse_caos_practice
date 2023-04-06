#include <time.h>
#include <stdio.h>

int main() {
    time_t t = time(NULL);
    printf("%lu\n", t);

    printf("year: %lu\n", t / 3600 / 24 / 365 + 1970);
    printf("hour: %lu\n", t / 3600 % 24);
}
