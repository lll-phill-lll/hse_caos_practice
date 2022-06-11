#include <iostream>
#include <thread>
#include <mutex>

int var;
std::mutex m;

void func(int n) {
    for (int i = 0; i != n; ++i) {
        // m.lock();
        std::lock_guard<std::mutex> lg(m);
        /*
        Больше про lock_guard можно найти здесь: https://en.cppreference.com/w/cpp/thread/lock_guard
        std::lock_guard эквивалентна mutex.lock() + mutex.unlock(). Эта функция безопаснее, так как при унитожении
        объекта lock_guard автоматически вызывается unlock, и не будет deadlock, если случится исключение до 
        момента unlock.  
        */
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
