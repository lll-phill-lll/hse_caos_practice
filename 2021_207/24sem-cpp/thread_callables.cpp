#include <iostream>
#include <thread>

struct A {
    void operator()() { // переопределяем оператор (), который не принимает аргументы
        std::cout << "A is called" << std::endl;
    }

    void operator()(int i) { // переопределяем оператор (), который принимает int
        std::cout << "A is called with param: " << i << std::endl;
    }
};

struct B {
    static void call_stat() {
        std::cout << "B static is called" << std::endl;
    }

    void call() {
        std::cout << "B is called" << std::endl;
    }
};


int main() {
    A a;
    std::thread t_a(a, 10); // вызывается тот оператор, который принимает аргумент int
                            // выводит "A is called with param: 10"
    // std::thread t_a(a); выводит "A is called"
    // Вывод: В зависимости от того, какие параметры передаются в thread, он может выбрать, какой из операторов класса позвать
    
    t_a.join();
    
    {
        B b;
        std::thread t_b(B::call_stat); // можем вызвать только static функции
        // Если функиця не static, то будет ошибка "invalid use of non-static member function"
        t_b.join();
        // выводит "B static is called"
    }
   
    {
        B b;
        std::thread t_b(&B::call, &b); // Чтобы вызвать non-static функцию, нужно указать функцию, которую
                                       // хотим вызвать, и объект, у которого эту функцию хотим вызвать
        t_b.join();
        // выводит "B is called"
    }

    
    
   // Еще можем передать lambda функцию
   int val = 5;
   std::thread t_l(
       [val]() {
           std::cout << "Lambda called with val=" << val << std::endl;
       }
   ); 
   t_l.join();
   // выводит "Lambda called with val=5"

    
    // Если хотим создать thread из другого thread, нужно использовать std::move
    // после move старая нить больше не существует.
    std::thread t_init(a);
    // std::thread t_new((t_init)); - ОШИБКА!!! Причина ошибки: use of deleted function
    // то есть нельзя скопировать thread
    std::thread t_new(std::move(t_init)); // можно! 

    t_new.join();
}
