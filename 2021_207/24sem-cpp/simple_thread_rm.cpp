#include <iostream>
#include <thread>

void thread_func() {
    std::cout << "hello world" << std::endl;
}

int main() {
    std::thread thr;
    thr(thread_func);
    // thr.join();
}
