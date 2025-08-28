#include <stdio.h>

// a * 2 + b
int multiply_add(int, int);

int main() {
    int a, b;

    scanf("%d", &a);
    scanf("%d", &b);

    int c = multiply_add(a, b);

    printf("%d\n", c);

}
