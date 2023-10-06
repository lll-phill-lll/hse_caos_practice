#include <iostream>
#include <cstdarg>

extern "C" void my_scan(const char* fmt, ...);

void scan(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while(*fmt) {
        if (*fmt == 'd') {
            int* loc = va_arg(args, int*);
            std::cin >> *loc;
        } else if (*fmt == 'l') {
            long long* loc = va_arg(args, long long*);
            std::cin >> *loc;
        }
        ++fmt;
    }
    va_end(args);
}


int main() {
    int i1, i2;
    long long ll1, ll2;

    // d - int(4)
    // l - long long(8)
    std::string fmt = "dldl";

    my_scan(fmt.c_str(), &i1, &ll1, &i2, &ll2);

    std::cout << "i1: " << i1 << std::endl;
    std::cout << "i2: " << i2 << std::endl;
    std::cout << "ll1: " << ll1 << std::endl;
    std::cout << "ll2: "<< ll2 << std::endl;

}
