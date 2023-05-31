#include <iostream>
#include <thread>
#include <future>

// Если мы хотим обработать исключение в другом потоке, то нужно немного запариться
void func(std::promise<int> p) {
    try {
        throw std::logic_error("hello");
    } catch (...) {
        // ловим сами же исключение и записываем его в promise.
        // Тогда читающий из future получит это исключение
        // Важно, что set_exception тоже может выкинуть собственное исключение
        p.set_exception(std::current_exception());
    }
}


int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();


    std::thread thr(func, std::move(p));
    try {
        // исключение прилетит при вызове .get()
        f.get();
    } catch (...) {
        std::cout << "fixed" << std::endl;
    }
    thr.join();
}
