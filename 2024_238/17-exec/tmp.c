#include <stdio.h>

int main() {
    int new_fd = dup(1);
    printf("%d\n", new_fd);
}





