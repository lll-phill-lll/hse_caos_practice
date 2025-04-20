#include "fib.h"
#include <cassert>
#include <iostream>

int main() {
    assert(Fib<0>::value == 0);
    assert(Fib<1>::value == 1);

    assert(Fib<2>::value  == 1);
    assert(Fib<3>::value  == 2);
    assert(Fib<5>::value  == 5);
    assert(Fib<10>::value == 55);
    assert(Fib<15>::value == 610);

    std::cout << "[  OK  ] All Fib tests passed\n";
    return 0;
}

