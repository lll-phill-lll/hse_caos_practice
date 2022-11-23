#include <iostream>
#include <thread> // Без .h, так как в C++ находимся!!!

void thread_func() {
    std::cout << "hello world" << std::endl;
}

int main() {
    std::thread thr(thread_func);

    thr.join(); // Обязательно использовать join, иначе будет ошибка типа "Aborted (Core dumped)"
    
    // std::thread thr2 = thr -- ОШИБКА!
    // Нельзя копировать threads, потому что иначе будет ошибка типа "Use of deleted function"
}
