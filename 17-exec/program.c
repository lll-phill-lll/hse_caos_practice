#include <stdio.h>

int main() {
    int o, e;
    scanf("%d %d", &o, &e);

    fprintf(stdout, "hello stdout: %d\n", o);
    fprintf(stderr, "hello stderr: %d\n", e);
}
