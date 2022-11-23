#include <iostream>
#include <thread>
#include <future>

struct A {
    A() {
        std::cout << "ctor" << std::endl;
    }

    A(const A& other) {
        std::cout << "copy ctor" << std::endl;
        i = other.i;
    }

    A(A&& other) {
        std::cout << "move ctor" << std::endl;
        i = other.i;
        other.i = 0;
    }
    int i;
};

void func(std::promise<A> p) {
    A a;
    a.i = 6;
    p.set_value(a);
}


int main() {
    std::promise<A> p;
    std::future<A> f = p.get_future();

    std::thread thr(func, std::move(p));
    thr.join();

    A res = f.get();

    std::cout << res.i << std::endl;
}
