#include <locale.h>
#include <time.h>
#include <stdio.h>

int main() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    setlocale(LC_TIME, "ru_RU.UTF-8"); // или "fr_FR.UTF-8", "de_DE.UTF-8" и т.д.

    char buf[100];
    strftime(buf, sizeof(buf), "%A %d %B %Y %H:%M:%S", tm);
    puts(buf);
}

