#include <stdio.h>
#include <stdlib.h>

int main() {

    void* p1 = malloc(4096);
    void* p2 = malloc(4096);
    void* p3 = malloc(4096);
    void* p4 = malloc(4096);

    // void* large = malloc(130 * 1024);

    printf("---------\n");
    printf("1: %p\n2: %p\n3: %p\n4: %p\n", p1, p2, p3, p4);
    printf("---------\n");

    free(p2);

    printf("---------\n");
    printf("1: %p\n2: %p\n3: %p\n4: %p\n", p1, p2, p3, p4);
    printf("---------\n");

    void* p5 = malloc(4096);

    printf("---------\n");
    printf("1: %p\n2: %p\n3: %p\n4: %p\n5: %p\n", p1, p2, p3, p4, p5);
    printf("---------\n");
}
