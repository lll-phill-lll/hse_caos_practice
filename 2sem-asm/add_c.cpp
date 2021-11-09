#include <iostream>

extern "C" int plus(int, int);

int main() {
    int a, b, c;
    std::cin >> a >> b;
    c = plus(a, b);
    std::cout << c << std::endl;
    return 0;
}
