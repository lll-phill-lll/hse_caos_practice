#include <stdio.h>

int main() {
    char c;
    int i;
    unsigned u;
    char s[64];

    scanf("%c", &c); // char
    printf("%c\n", c);

    scanf("%d", &i); // digit
    printf("%d\n", i);

    scanf("%u", &u); // unsigned
    printf("%u\n", u);

    scanf("%s", s); // string
    printf("%s\n", s);
}

