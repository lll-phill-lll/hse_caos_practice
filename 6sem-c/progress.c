#include <unistd.h>
#include <stdio.h>

enum {
    PERCENT = 5,
    LEN = 100 / PERCENT,
};

void print(unsigned p) {
    int p_ = p / PERCENT;

    printf("\r[");

    for (int i = 0; i != p_; ++i) {
        printf("-");
    }
    printf(">");

    for (int i = p_; i < LEN-1; ++i) {
        printf(" ");
    }

    printf("]%4u%%", p);

    fflush(stdout);
}

void f() {
    sleep(1);
}

int main() {
    print(0);
    for (int i = 0; i <= LEN; ++i) {
        f();
        print(i*PERCENT);
    }
    printf("\n");
}
