#include <iostream>
#include <thread>
#include <mutex>

int var;
std::mutex m;

// Пусть у нас есть сложная критическая секция, в которой надо использовать мьютекс
void func(int n) {
    for (int i = 0; i != n; ++i) {
        // можно использовать m.lock(), m.unlock(),
        // но тогда нужно будет следить дополнительно за тем,
        // чтобы не было исключений или не сделать return слишком рано. В противном
        // случае можем забыть сделать unlock и получим дэдлок
        //
        // Чтобы решить проблему, существует std::lock_guard или std::scoped_lock,
        // в своем деструкторе они отпускают блокировку
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
