#include <stdio.h>
#include <string.h>

int main() {
    char input[9];
    char password[9] = "password";

    scanf("%8s", input);

    if (strcmp(input, password) == 0) {
        printf("Access granted\n");
    } else {
        printf("Access denied\n");
    }

    printf("Correct password: %s\n", password);
}

