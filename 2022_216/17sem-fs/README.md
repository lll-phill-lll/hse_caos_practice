# 17 Семинар 04.04.2022 Time
## Файлики с кодом:
* [Простой пример функции time](time.c)
* [Пример структуры tm, функции mktime](localtime.c)
* [Пример функции asctime](asctime.c)
* [Пример переполнения времени](localtime_overflow.c)
* [Пример функции asctime-2](asctime_change.c)
* [Пример функции strftime](strtime.c)
* [Пример функции strptime](strptime.c)
* [Пример структуры timeval и функции gettimeofday](gettimeofday.c)
* [Пример функции clock_gettime](clock_gettime.c)
* [Считаем время выполнения ребенка](times.c)

## Структуры timeval и tm
```c
struct timeval {
time_t tv_sec; /* секунды */
long tv_usec; /* микросекунды */
};
```

```c
struct tm { /* время, разбитое на составляющие */
int tm_sec; /* секунды от начала минуты: [0 -60] */
int tm_min; /* минуты от начала часа: [0 - 59] */
int tm_hour; /* часы от полуночи: [0 - 23] */
int tm_mday; /* дни от начала месяца: [1 - 31] */
int tm_mon; /* месяцы с января: [0 - 11] */
int tm_year; /* годы с 1900 года */
int tm_wday; /* дни с воскресенья: [0 - 6] */
int tm_yday; /* дни от начала года (1 января): [0 - 365] */
int tm_isdst; /* флаг перехода на летнее время: <0, 0, >0 */
};
```
## Используемые функции
#### time
```c
#include <time.h>
time_t time(time_t *calptr);
```
* Возвращает количество секунд, прошедших от начала Эпохи – 00:00:00 1 января 1970, в случае успеха
* Возвращает –1 в случае ошибки.


#### gettimeofday
```c
#include <sys/time.h>
int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
```
Функция gettimeofday сохраняет время, прошедшее от начала Эпохи до настоящего момента, по адресу tp.

#### localtime
```c
#include <time.h>
struct tm *localtime(const time_t *calptr);
```
Функция localtime превращает time_t в структуру tm.

#### mktime
```c
#include <time.h>
time_t mktime(struct tm *tmptr);
```
* Функция mktime пересчитает структуру tm и превращает ее в time_t.
* Возвращает –1 в случае ошибки

#### asctime & ctime
```c
#include <time.h>
char *asctime(const struct tm *tmptr);
char *ctime(const time_t *calptr);
char *asctime_r(const struct tm *tm, char *buf);
char *ctime_r(const time_t *timep, char *buf);
```
Превращает структуру tm или time_t в строку \
Функции с суффиксом `r` отличаются от обычных тем, что функции без суффикса `r` принимают в себя только `struct tm` или `time_t`. То есть они используют какой-то внутренний буффер. А чтобы применить функции с суффиксом `r` (например, `ctime_r`, `asctime_r`), пользователю нужно сам задать буффер. Например, `char[] buff;`.

#### strftime
```c
#include <time.h>
size_t strftime(char *restrict buf, size_t maxsize, const char *restrict format,const struct tm *restrict tmptr);
```
* Представляет структуру tm в виде отформатированной строки.
* Возвращает 0 в случае ошибки

## References
* [Лекция с физтеха (time)](https://github.com/victor-yacovlev/mipt-diht-caos/tree/master/practice/time)
* [Прошлый год](https://github.com/blackav/hse-caos-2020/tree/master/12-files2#%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0-%D1%81%D0%BE-%D0%B2%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%B5%D0%BC)
