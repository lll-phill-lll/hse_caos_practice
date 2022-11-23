#include <time.h>
#include <stdio.h>
#include <limits.h>

int main() {
    time_t t = INT_MAX;
    t += 1; // ничего не сломается, потому что у нас все сохраняется в 64-битном виде
            // если с флагом -m32, то год как-то = 1901
    printf("%lu\n", t);

    // consider ctime_r
    char* ctime_res = ctime(&t);
    printf("%s", ctime_res);
}
