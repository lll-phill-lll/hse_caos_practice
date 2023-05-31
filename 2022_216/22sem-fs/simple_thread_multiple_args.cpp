#include <iostream>
#include <thread>

struct A {
    A() {
        std::cout << "ctor" << std::endl;
    }
    A(const A&) {
        std::cout << "copy ctor" << std::endl;
    }

    A(A&&) {
        std::cout << "move ctor" << std::endl; // move конструктор
    }

};

void thread_sum(int i, int j) {
    std::cout << "hello sum: " << i + j  << std::endl;
}

void thread_append(A a) {
}

int main() {
    std::thread t_sum(thread_sum, 5, 6);
    t_sum.join();

    std::string greetings = "hello";
    A a;
    std::thread t_append(thread_append, a);
    // std::thread t_append(thread_append, std::ref(a));
    // std::thread t_append(thread_append, std::move(greetings));


    t_append.join();

    std::cout << greetings << std::endl;
}
