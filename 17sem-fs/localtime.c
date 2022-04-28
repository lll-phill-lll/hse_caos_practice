#include <time.h>
#include <stdio.h>

void print_tm(struct tm timeinfo) {
    // struct tm - время, разбитое на составляющие
    printf("tm_sec:   %d\n"
           "tm_min:   %d\n"
           "tm_hour:  %d\n"
           "tm_mday:  %d\n"
           "tm_mon:   %d\n"
           "tm_year:  %d\n"
           "tm_wday:  %d\n"
           "tm_yday:  %d\n"
           "tm_isdst: %d\n",
           timeinfo.tm_sec, // секунды от начала минуты: [0 -60]
           timeinfo.tm_min, // минуты от начала часа: [0 - 59]
           timeinfo.tm_hour, // часы от полуночи: [0 - 23]
           timeinfo.tm_mday, // дни от начала месяца: [1 - 31]
           timeinfo.tm_mon, // месяцы с января: [0 - 11]
           timeinfo.tm_year, // годы с 1900 года
           timeinfo.tm_wday, // дни с воскресенья: [0 - 6]
           timeinfo.tm_yday, // дни от начала года (1 января): [0 - 365]
           timeinfo.tm_isdst); // флаг перехода на летнее время
                               // флаг > 0, если действует летнее время
                                // флаг == 0, если НЕ действует летнее время
                                // флаг < 0, если данная информация недоступна
}

int main() {
    time_t t = time(NULL);
    printf("%lu\n", t);

    struct tm* timeinfo; // структура объявлена внутри localtime как буффер. Это ведет к проблеме, 
                           // что кто-то может поменять эту дату в системе. 
                            // Есть механизм защиты: struct tm *localtime_r( const time_t *timer, struct tm *buf );

    timeinfo = localtime(&t); // превращает time_t в struct tm

    timeinfo->tm_hour += 100; // выводит 113 часов. Это неправильно. Нужна функция mktime
    print_tm(*timeinfo);
    printf("--------\n");

    mktime(timeinfo); // пересчитает timeinfo

    print_tm(*timeinfo); // выводит 17 часов. Это правильно
    printf("--------\n");
}
