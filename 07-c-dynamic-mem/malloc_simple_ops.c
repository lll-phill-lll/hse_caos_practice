#include <stdio.h>
#include <stdlib.h>

typedef struct s {
    int i;
    char c;
} MyStruct;

int main() {

    MyStruct* p = calloc(1, sizeof(*p));
    if (p == NULL) {
        return 1;
    }

    p->i = 5;
    p->c = 'a';

    MyStruct* p2 = realloc(p, 2 * sizeof(*p));
    if (p2 == NULL) {
        return 1;
    }

    p = p2;

    printf("%d, %c\n", p->i, p->c);

    free(p);
}
