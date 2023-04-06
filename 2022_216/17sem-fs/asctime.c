#include <time.h>
#include <stdio.h>


int main() {
    time_t t = time(NULL);
    printf("%lu\n", t);

    // consider ctime_r
    char* ctime_res = ctime(&t);
    printf("%s", ctime_res);

    struct tm* timeinfo;

    timeinfo = localtime(&t);

    // consider asctime_r
    char* asctime_res = asctime(timeinfo);
    printf("%s", asctime_res);



}
