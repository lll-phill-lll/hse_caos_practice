// test_averegator.c
#include <stdio.h>
#include <stdlib.h>
#include "averegator.h"

void testFull() {
    int numbers[] = {1, 2, 3, 4, 5};
    double result = average(numbers, 5);
    if (result != 3.0) {
        printf("Test failed: expected 3.0, got %.2f\n", result);
        exit(1);
    } else {
        printf("Test passed: average function\n");
    }
}

int main() {
    testFull();
    return 0;
}

