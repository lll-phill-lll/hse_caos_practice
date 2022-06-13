#include <iostream>
#include <thread>

struct A {
    A() {
        std::cout << "ctor" << std::endl; // конструктор
    }
    A(const A&) {
        std::cout << "copy ctor" << std::endl; // конструктор копирования
    }

    //A(A&&) {
    //    std::cout << "move ctor" << std::endl; // move конструктор
    //}

};

void thread_sum(int i, int j) {
    std::cout << "hello sum: " << i + j  << std::endl;
}

void thread_append(A s) {
    s += " world";
}

int main() {
    std::thread t_sum(thread_sum, 5, 6); // В С++ возможно передавать еще аргументы функции. Для этого 
                                         // просто через запятую перечисляем аргументы, которые хотим передать 
                                        // Можно передать любое количество аргументов, но оно должно
                                        // совпасть с количеством аргументов функции, которую вызываем. Иначе код 
                                        // не компилируется.
    t_sum.join();

    std::string greetings = "hello";
    A a;
    std::thread t_append(thread_append, a);
    // std::thread t_append(thread_append, std::ref(a)); // Когда хотим передать по ссылке, используем std::ref. ref отличается
                                                        // от & тем, что ref - полноценный объект, у которого есть конструктор и деструктор,
                                                        // и он корректно передается.
                                                        // Если передаем просто a, то помимо самого конструктора еще вызывается 3 раза конструктор 
                                                        // копирования, что не выгодно. С ref только сам конструктор вызывается.
   
    // std::thread t_append(thread_append, std::move(a)); // Если передаем move(a), то вызывается 1 раз сам конструктор, 1 раз копирование, 2 раза move
   

    t_append.join(); //

    std::cout << greetings << std::endl;
}
