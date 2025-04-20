#include "julia.h"
#include "fib.h"


constexpr int OFFSET = Fib<60>::value % 50;

int julia(double x, double y, int max_iter, double cx, double cy) {
    int i = 0;
    while (x*x + y*y <= 4.0 && i < max_iter + OFFSET) {
        double xt = x*x - y*y + cx;
        y = 2*x*y + cy;
        x = xt;
        i++;
    }
    return i;
}
