#include <iostream>
#include <thread>

// передаем копию
void thread_append(std::string s) {
    s += " world!";
}

// передаем через move
void thread_append_move(std::string s) {
    s += " world!";
}

// передаем через ref/cref
void thread_append_ref(std::string& s) {
    s += " world!";
}

int main() {
    {
        std::string greetings("Hello");
        // во время создания потока аргументы передаются или копией или мувом.
        std::thread t(thread_append, greetings);
        t.join();
        std::cout << greetings << std::endl;
        // cout: Hello
    }

    {
        std::string greetings("Hello");
        // уменьшили количество копий строки, но потеряли владение объектом
        std::thread t(thread_append_move, std::move(greetings));
        t.join();
        // отдали владение строкой в функцию. Теперь вывести ее не можем
        std::cout << greetings << std::endl;
        // cout:
    }

    {
        std::string greetings("Hello");
        // обернули greetings в std::reference_wrapper, он там сколько-то раз
        // покопировался/помувался и так как "they are implicitly convertible to T&, so that they can be used as arguments with the functions that take the underlying type by reference."
        // мы можем в функции принять такой объект просто по ссылке.
        // Также есть std::cref для константных ссылок
        std::thread t(thread_append_ref, std::ref(greetings));
        t.join();
        std::cout << greetings << std::endl;
        // cout: Hello world!
    }
}
