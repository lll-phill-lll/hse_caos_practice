#include <time.h>
#include <stdio.h>
#include <limits.h>

int main() {
    time_t t = INT_MAX;
    t += 1;
    printf("%lu\n", t);

    // consider ctime_r
    char* ctime_res = ctime(&t);
    printf("%s", ctime_res);
}
