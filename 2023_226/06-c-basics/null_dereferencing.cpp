#include <iostream>

// Пример взят отсюда:
// https://kristerw.blogspot.com/2017/09/why-undefined-behavior-may-call-never.html

// Пример разного поведения программы при разном уровне оптимизации:

// clang++ -O0 - segmentation fault (UB)
// clang++ -O3 - week of regret (UB)
// ﻿﻿clang version 10.0.0-4ubuntu1 
// Target: x86_64-pc-linux-gnu


// Почему так происходит?
// Компилятор имеет право считать, что в нашем коде никогда не произойдет UB. Поэтому исходя из этого предположения делает какие-то оптимизации.

// Проблема
// func_t - тип указателя на функцию с сигнатурой int ()
// Так как func - static, то изначально она инициализированна 0
// Дальше мы делаем func() - то есть разыменовываем null - что является UB.

// Почему вызовется call_your_ex?
// В данном простом коде компилятор видит, что значение функции func может быть или 0, или call_your_ex.
// Дальше у нас есть вызов func - значит там не 0, потому что компилятор действует в предположении, что UB не бывает
// А значит единственный вариант, который может быть в func - call_your_ex. При этом у нас даже есть код, который присваивает func = call_your_ex.
// этот код потенциально может быть вызван откуда-то. Поэтому компилятор делает оптимизацию и сразу же делает return call_your_ex.



typedef int (*func_t)();

static func_t func;

int call_your_ex() {
    std::cout << "Week of regret" << std::endl;
    return 0;
}

void never_called() {
    func = call_your_ex;
}

int main() {
    return func();
}
