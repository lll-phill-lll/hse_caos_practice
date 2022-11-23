#include <iostream>
#include <thread>
#include <future>

/* Как получить значения, которые возвращаются из функции?
Для этого создаем promise и future. Они работают аналогично каналу. 
В promise будем записывать, из future - забирать
*/

void func(std::promise<int> p) {
    p.set_value(123);  // пишем 123 в promise
}

int main() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread thr(func, std::move(p)); // в thread передаем promise, чтобы thread знал, куда записать
    // promise нельзя скопировать, поэтому используем move.

    int res = f.get(); // забираем значение от future

    thr.join();


    std::cout << res << std::endl;

    // exception
    // res = f.get(); механизм работает только 1 раз.
    // Если 2 раза забираем значение от future, будет ошибка: no associated state
}
