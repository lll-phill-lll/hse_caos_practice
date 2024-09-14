#include <math.h>
#include <stdio.h>

double myhypot(double, double);

int main() {
    double a, b;
    scanf("%lf", &a);
    scanf("%lf", &b);

    double res = myhypot(a, b);
    printf("My:\t%lf\n", res);

    res = hypot(a, b);
    printf("Lib:\t%lf\n", res);
    return 0;
}
