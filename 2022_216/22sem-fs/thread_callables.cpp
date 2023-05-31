#include <iostream>
#include <thread>

// объявляет оператор (), теперь можно сделать так:
// A a;
// a();
// и вызовется код оператора
struct A {
    void operator()() {
        std::cout << "A is called" << std::endl;
    }

    void operator()(int i) {
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
    // можем передать в поток также callable. например, объект класса, у которого определен оператор ()
    A a;
    // можем вызвать оператор без аргументов
    std::thread t_a(a);
    // cout: A is called
    t_a.join();

    // можем вызвать с аргументами
    std::thread t_a_param(a, 5);
    // cout: A is called with param: 5
    t_a_param.join();


    // можно в качестве функции передать статический метод класса
    {
        std::thread t_b(B::call_stat);
        t_b.join();
    }

    // но нельзя передать нестатический
    // {
    //     B b;
    //     std::thread t_b(B::call);
    //     t_b.join();
    // }

    // Но если следующим аргументом передать указатель на объект класса, то нестатический метод
    // все-таки вызвать можно.
    {
        B b;
        std::thread t_b(&B::call, &b);
        t_b.join();
    }

    // Также в поток можно передать лямбду
    //
    // greetings захватим
    std::string greetings("Hello");
    // name передадим в качестве аргумента
    std::string name("Misha");
    std::thread t_l(
            // захватываем greetings по ссылке
            [&greetings](std::string& name) {
                std::cout << "Lambda called captured: " << greetings
                << ", and passed by argument: " << name << std::endl;
                greetings += ", ";
                greetings += name;
       },
       // передаем name по ссылке как аргумент, оборачивая в reference_wrapper, чтобы ссылку не
       // потерять
       std::ref(name)
    );
    t_l.join();
    std::cout << greetings << std::endl;
    // cout: Hello, Misha
}
