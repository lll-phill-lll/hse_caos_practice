// ** Условие **
// Из кода c/c++ вызывается функция int plus(int, int)
// написать эту функцию на ассемблере

#include <stdio.h>

// объявляем функцию, которую будем искать в asm
int plus(int, int);

int main() {
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    c = plus(a, b);
    printf("%d\n", c);
    return 0;
}
