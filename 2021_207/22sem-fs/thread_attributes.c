#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

void* func(void* smth) {
    printf("hello\n");
    return NULL;
}

int main() {
    pthread_t tids[N];

    pthread_attr_t attr; // Создаем аттрибуты
    pthread_attr_init(&attr); // Инициализируем аттрибуты 
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN /*можно взять из конфига*/)); // меняем размер стека
    pthread_attr_setguardsize(&attr, 0);  // меняем размер дополнительного места стека

    // 1MB
    // int res = pthread_attr_setstacksize(&attr, 10);
    // if (res) {
    //     printf("failed\n");
    // }

    printf("%ld\n", sysconf(_SC_THREAD_STACK_MIN));
    for (int i = 0; i != N; ++i) {
        /*  int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
        */
        pthread_create(&tids[i], &attr, func, NULL);
    }
    pthread_attr_destroy(&attr);

    for (int i = 0; i != N; ++i) {
        /* дожидаемся отработки каждого потока. всего будет n+1 потоков 
           Функция возвращает void*, поэтому можно передать то, куда складывать возвращаемое значение
        */
        pthread_join(tids[i], NULL);
    }
}
