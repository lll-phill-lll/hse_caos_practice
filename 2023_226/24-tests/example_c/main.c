// main.c
#include <stdio.h>
#include <stdlib.h>

#include "averegator.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: ./main число1 число2 число3 ...\n");
        return 1;
    }

    int *numbers = malloc(sizeof(int) * (argc - 1));
    if (numbers == NULL) {
        perror("Ошибка выделения памяти");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        numbers[i - 1] = atoi(argv[i]);
    }

    printf("Числа: ");
    for (int i = 0; i < argc - 1; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    printf("Среднее значение: %.2f\n", average(numbers, argc - 1));

    free(numbers);
    return 0;
}

