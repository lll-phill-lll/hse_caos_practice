#include <iostream>
#include <thread>

struct A {
    void call_A() {
        std::cout << "val: " << val << std::endl;
    }

    int val;
};

struct B : public A {
    void call_B() {
        std::cout << "B 2 is called" << std::endl;
    }
};


int main() {
    // call method of B
    {
        B b;
        std::thread t_b(&B::call_B, &b);
        t_b.join();
    }

    // call method of A
    {
        B b;
        b.val = 42;
        std::thread t_b(&A::call_A, &b);
        t_b.join();
    }
}
