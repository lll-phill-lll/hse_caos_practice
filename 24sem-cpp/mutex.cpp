#include <iostream>
#include <thread>
#include <mutex>

int var;
std::mutex m;

void func(int n) {
    for (int i = 0; i != n; ++i) {
        // m.lock();
        std::lock_guard<std::mutex> lg(m);
        var += i;
        // m.unlock()
    }
}


int main() {
    std::thread thr1(func, 10000);
    std::thread thr2(func, 10000);

    thr1.join();
    thr2.join();

    std::cout << var << std::endl;
}
