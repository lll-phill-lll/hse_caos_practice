#include <stdio.h>

int call() {
    return 1;
}


int main() {
    if (call()) {
        printf("hello");
    }
}
