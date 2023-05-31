#include <iostream>
#include <thread>

void thread_func(int i) {
    std::cout << "hello world " << i << std::endl;
}

int main() {
    std::thread thr(thread_func, 2);
    // join делать обязательно
    thr.join();
    // thr.detach();


    std::thread thr2(std::move(thr));
    thr2.join();
}
