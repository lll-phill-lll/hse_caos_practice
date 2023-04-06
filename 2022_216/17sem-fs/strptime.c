#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[]) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));

    strptime(argv[1], "%Y-%m-%d_%H:%M:%S", &tm);

    char date[255];
    strftime(date, sizeof(date), "%d %b %Y %H:%M, %a", &tm);
    printf("%s\n", date);
}
