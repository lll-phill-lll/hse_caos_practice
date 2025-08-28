#include <stdio.h>

int count_digits(char* input);

int main() {
    char input[101];

    scanf("%100s", input);

    int count = count_digits(input);

    printf("%d\n", count);
}
