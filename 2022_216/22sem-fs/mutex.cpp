#include <iostream>
#include <thread>
#include <mutex>

int var;
std::mutex m;

void func(int n) {
    for (int i = 0; i != n; ++i) {
        std::lock_guard<std::mutex> lg(m);
        var += 1;
    }
}


int main() {
    std::thread thr1(func, 1000000);
    std::thread thr2(func, 1000000);

    thr1.join();
    thr2.join();

    std::cout << var << std::endl;
}
