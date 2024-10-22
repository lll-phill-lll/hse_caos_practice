#include <stdio.h>

int main() {
    char c;
    int i;
    unsigned u;
    long long ll;
    char s[64];

    scanf("%c", &c);        // char
    printf("Char: %c, int: %d\n", c, c);

    scanf("%d", &i);        // int
    printf("Int: %d\n", i);

    scanf("%u", &u);        // unsigned
    printf("Unsigned: %u\n", u);

    scanf("%llx", &ll);     // hex long long
    printf("Hex long long: %lld\n", ll);

    // don't forget size
    scanf("%s", s);         // string
    printf("String: %s\n", s);
}

