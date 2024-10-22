#include <iostream>


typedef int (*func_t)();

static func_t func;

int call_your_ex() {
    std::cout << "Week of regret" << std::endl;
    return 0;
}

void never_called() {
    func = call_your_ex;
}

int main() {
    return func();
}
