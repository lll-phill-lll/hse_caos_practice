#include <stdio.h>

int main() {
    char c = 'c';
    int i = 100;
    unsigned u = 12;
    float f = 12.22;

    char str[] = "hello world";

    printf("%c\n", c);
    printf("%d\n", c);
    printf("%d\n", i);
    // what number
    printf("%d\n", str);
    printf("%u\n", u);
    printf("%f\n", f);
    printf("%.2f\n", f);

    printf("%d, `%c\n", c, i);
}
