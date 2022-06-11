#include <stdio.h>
#include <math.h>

void myhypot(double, double, double *);

int main() {
    double a, b;
    scanf("%lf", &a);
    scanf("%lf", &b);

    double res = 0;
    myhypot(a, b, &res);
    printf("%lf\n", res);

    res = hypot(a, b);
    printf("%lf\n", res);
    return 0;
}
