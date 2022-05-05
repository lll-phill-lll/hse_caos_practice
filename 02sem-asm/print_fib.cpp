#include <iostream>

extern "C" void print_fib(int, int);

int main() {
    int a, b;
    std::cin >> a >> b;
    print_fib(a, b);
    return 0;
}
