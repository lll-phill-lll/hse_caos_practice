#include <iostream>
#include <thread>
#include <future>

void func(std::promise<int> p) {
    try {
        throw std::logic_error("hello");
    } catch (...) {
        // set_exception тоже может кидать exception.
        p.set_exception(std::current_exception()); // Нужно в promise записать exception
        // current_exception - то исключение, которое сейчас случилось.
    }
}


int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread thr(func, std::move(p));
    
    // поймаем исключение
    try {
        f.get();
    } catch (...) {
        std::cout << "fixed" << std::endl;
    }
    thr.join();
}
