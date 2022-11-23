#include "stdio.h"

void foo(double a, double b) {
    printf("%lf\n", a + b);
}

int main() {
    double a = 1.0;
    double b = 2.0;
    foo(a, b);
}
