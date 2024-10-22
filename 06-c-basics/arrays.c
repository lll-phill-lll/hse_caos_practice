#include <stdio.h>

void ChangeArray(int* array) {
    // array[0] = 11;
    *array = 11;

    printf("%s: %ld\n", __func__, sizeof(array));
}

int main() {

    int array[] = {1, 2, 3};
    int size = sizeof(array);

    printf("%d\n", *(array-1));

    for (int i = 0; i < 3; ++i) {
        printf("%d\n", array[i]);
    }
    printf("Array size: %ld\n", sizeof(array) / sizeof(array[0]));

    int* parray = array;

    for (int i = 0; i < 3; ++i) {
        printf("%d\n", *(parray + i));
    
    }

    printf("PArray size: %ld\n", sizeof(parray));

    ChangeArray(array);

    for (int i = 0; i < 3; ++i) {
        printf("%d\n", *(array + i));
    }

}
