#include <stdlib.h>
#include <stdio.h>

// Так узнавать размер алокации нельзя.
// Это просто демонстрация устройства аллокатора
size_t get_allocated_size(void *ptr) {
    return *((size_t *)ptr - 1);
}

int main() {

    void* p = malloc(10000);
    printf("%ld\n", get_allocated_size(p));
}
