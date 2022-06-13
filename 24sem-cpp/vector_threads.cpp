#include <iostream>
#include <thread>
#include <future>
#include <vector>

// Работаем с 5 потоками

void func(std::promise<int> p, int i) {
    p.set_value(i + 100);
}


int main() {
    // Нужны 2 контейнера: в одном храним threads, чтобы потом вызвать join
    // в другом храним futures, чтобы получить результаты функций
    std::vector<std::thread> threads;
    std::vector<std::future<int>> futures;
    
    for (int i = 0; i != 5; ++i) {
        std::promise<int> p;
        futures.push_back(p.get_future()); // здесь вызывается move конструктор 
        threads.push_back(std::thread(func, std::move(p), i));
    }

    // пытаемся получить результаты
    for (int i = 0; i != 5; ++i) {
        int res = futures[i].get(); // результаты получаем по порядку, так как get блокируется.
        std::cout << res << std::endl;
    }

    for (int i = 0; i != 5; ++i) {
        threads[i].join();
    }

}
