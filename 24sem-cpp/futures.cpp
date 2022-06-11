#include <iostream>
#include <thread>
#include <future>

void func(std::promise<int> p) {
    p.set_value(123);
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread thr(func, std::move(p));

    int res = f.get();

    thr.join();


    std::cout << res << std::endl;

    // exception
    // res = f.get();
}
