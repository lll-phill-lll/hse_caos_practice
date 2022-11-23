#include <time.h>
#include <stdio.h>


int main() {
    time_t t = time(NULL);
    printf("%lu\n", t);

    // consider ctime_r
    char* ctime_res = ctime(&t); // возвращает строку из time_t
                                  // Tue Apr 5 13:49:25 2022\n\0
    printf("%s", ctime_res);

    struct tm* timeinfo;

    timeinfo = localtime(&t);

    // consider asctime_r
    char* asctime_res = asctime(timeinfo); // возвращает строку из struct tm
                                            // Tue Apr 5 13:49:25 2022\n\0
    printf("%s", asctime_res);



}
