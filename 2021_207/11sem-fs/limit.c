/*
 *
 * Узнаем ограничения на процессы, созданные пользователем
 *
 */
#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit a;
    int res = getrlimit(RLIMIT_NPROC, &a);
    printf("%ld %ld\n", a.rlim_cur, a.rlim_max);
}
