#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 10

pthread_t tids[N];

int arr[N];

int num;

void* func(void* smth) {
    int arr_num = (int)(intptr_t)(smth);
    if (arr_num == 0) {
        arr[arr_num] = 5;
        return NULL;
    }

    int prev_arr_num = arr_num - 1;


    printf("%d waiting for %d\n", arr_num, prev_arr_num);
    pthread_join(tids[prev_arr_num], NULL);

    arr[arr_num] = arr[prev_arr_num] + 10;

    return NULL;
}

int main() {
    for (int i = 0; i != N; ++i) {
        pthread_create(&tids[i], NULL, func, (void *)(intptr_t)i);
    }

    printf("%d waiting for %d\n", 0, N - 1);
    pthread_join(tids[N - 1], NULL);

    printf("Arr:\n");
    for (int i = 0; i != N; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
