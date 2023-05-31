#include <iostream>
#include <thread>
#include <future>

int func(int i) {
    // Исключения в async кидаются тоже приятнее
    throw std::logic_error("hello");
    return 123 + i;
}

int main() {
    std::future<int> f = std::async(func, 1);

    int res;
    try {
        // аналогично тому, как мы делали в thread
        res = f.get();
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    std::cout << res << std::endl;
}
