#include <iostream>
#include <thread>
#include <future>

int func(int i) {
    return 123 + i;
}

int main() {
    std::future<int> f = std::async(std::launch::deferred, func, 1);

    int res;
    res = f.get();

    std::cout << res << std::endl;
}
