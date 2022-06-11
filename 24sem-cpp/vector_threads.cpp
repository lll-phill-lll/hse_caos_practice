#include <iostream>
#include <thread>
#include <future>
#include <vector>

void func(std::promise<int> p, int i) {
    p.set_value(i + 100);
}


int main() {
    std::vector<std::thread> threads;
    std::vector<std::future<int>> futures;

    for (int i = 0; i != 5; ++i) {
        std::promise<int> p;
        futures.push_back(p.get_future());

        threads.push_back(std::thread(func, std::move(p), i));
    }


    for (int i = 0; i != 5; ++i) {
        int res = futures[i].get();
        std::cout << res << std::endl;
    }

    for (int i = 0; i != 5; ++i) {
        threads[i].join();
    }

}
