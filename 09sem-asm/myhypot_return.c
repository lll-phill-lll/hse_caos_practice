#include <stdio.h>
#include <math.h>

double myhypot(double, double);

int main() {
    double a, b;
    scanf("%lf", &a);
    scanf("%lf", &b);

    double res = myhypot(a, b);
    printf("%lf\n", res);

    res = hypot(a, b);
    printf("%lf\n", res);
    return 0;
}
