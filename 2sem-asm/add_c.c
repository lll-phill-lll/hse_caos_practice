#include <stdio.h>

int plus(int, int);

int main() {
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    c = plus(a, b);
    printf("%d\n", c);
    return 0;
}
