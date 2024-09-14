#include <iostream>
#include <cstdarg>

extern "C" int my_add_nums(int count, ...);

int add_nums(int count, ...) {
    va_list args;
    va_start(args, count);

    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += va_arg(args, int);
    }
    va_end(args);

    return sum;
}


int main() {
    std::cout << my_add_nums(3, 99, 1, 2, 3, 4, 5) << std::endl;

}
