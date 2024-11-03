#include <stdio.h>
#include <stdlib.h>

typedef struct s {
    int i;
    char c;
} MyStruct;

int main() {
    printf("%ld\n", sizeof(MyStruct));

    int num = 10;

    MyStruct* p = calloc(num, sizeof(*p));
    if (p == NULL) {
        perror("malloc");
        exit(1);
    }

    for (int i = 0; i < num; ++i) {
        (p+i)->i = i * i;
        (p+i)->c = 'a' + i;
    }

    MyStruct* tmp = realloc(p, num * sizeof(*p) * 2);
    if (tmp == NULL) {
        free(p);
        perror("realloc");
        exit(1);
    }
    p = tmp;

    for (int i = num; i < 2 * num; ++i) {
        (p+i)->i = i;
        (p+i)->c = '0' + i;
    }


    for (int i = 0; i < num * 2; ++i) {
        printf("%d, %c\n", p[i].i, p[i].c);
    }

    free(p);
}
