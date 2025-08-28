#include <iostream>

void hello(int& num) { num /= 16; }

int lol(int number) {
    number = 55;
    return number % 7;
}

void something(int& val, int var) { val -= var * 3; }

int world(int num) {
    ++num;
    return num;
}

void update(int u) { u += 14; }

void trunk(int& n) {
    if (n > 20) n /= 22;
}

void make(int& i) { --i; }

void foo(int& val) {
    int var = lol(val);

    int& param = val;

    if (var % 2) {
        hello(val);
    } else {
        var = world(var);
        something(param, var);

        val -= var;
    }

    trunk(param);

    make(param);

    update(val);
}

int main() {
    int i = 50;

    foo(i);
    if (i == 0) {
        std::cerr << "ERROR! i is 0" << std::endl;
        exit(1);
    }

    std::cout << "SUCCESS! i is " << i << std::endl;
}

