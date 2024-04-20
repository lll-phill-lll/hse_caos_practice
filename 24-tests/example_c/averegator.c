// averegator.c
#include "averegator.h"

double average(int *numbers, int size) {
    if (size == 0) {
        return 0;
    }
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }
    
    return (double) sum / size;
}

