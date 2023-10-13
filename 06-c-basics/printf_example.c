#include <stdio.h>

int main() {
    char c = 'c';
    int i = 100;
    unsigned u = 12;
    float f = 12.22;

    char str[] = "hello world";

    printf("%c\n", c);      // char
    printf("%d\n", c);      // digit
    printf("%d\n", i);      // digit
    printf("%x\n", i);      // hex
    printf("%d\n", str);    // digit
    printf("%u\n", u);      // unsigned
    printf("%x\n", -1);     // hex
    printf("%f\n", f);      // float
    printf("%.2f\n", f);    // float 2 знака после запятой

    printf("%d, %c\n", c, i);
}
