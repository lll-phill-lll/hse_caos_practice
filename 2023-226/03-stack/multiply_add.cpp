#include <iostream>

// a * 2 + b
// extern "C" нужно для того, чтобы имя функции сконструировалось
// по правилам C
extern "C"
int multiply_add(int, int);


int main() {
    int a, b;

    std::cin >> a;
    std::cin >> b;

    int c = multiply_add(a, b);

    std::cout << c << std::endl;
}
