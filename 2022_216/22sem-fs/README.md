# [22 Семинар 30.05.2023 Нити С++](https://disk.yandex.ru/d/hVWLMgTBxXHBUQ/%D0%90%D1%80%D1%85%D0%B8%D1%82%D0%B5%D0%BA%D1%82%D1%83%D1%80%D0%B0%20%D0%BA%D0%BE%D0%BC%D0%BF%D1%8C%D1%8E%D1%82%D0%B5%D1%80%D0%B0%20%D0%B8%20%D0%BE%D0%BF%D0%B5%D1%80%D0%B0%D1%86%D0%B8%D0%BE%D0%BD%D0%BD%D1%8B%D0%B5%20%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D1%8B/%D0%A1%D0%B5%D0%BC%D0%B8%D0%BD%D0%B0%D1%80/%D0%91%D0%9F%D0%9C%D0%98216%20%D0%A4%D0%B8%D0%BB%D0%B8%D1%82%D0%BE%D0%B2%202023-05-30T11-31-01Z.mp4)
## Файлики с кодом:
* [Thread](simple_thread.cpp)
* [Передача в поток аргументов по ссылке](thread_pass_arguments_by_ref.cpp)
* [Передача в поток callable](thread_callables.cpp)
* [mutex, lock_guard](mutex.cpp)
* [Future/promise](futures.cpp)
* [Обработка исключений](exceptions.cpp)
* [Async](async.cpp)
* [Обработка исключений в async](async_exceptions.cpp)
* [Несколько потоков, несколько пар promise-future](vector_threads.cpp)

## Класс `std::thread`
* Класс `std::thread` объявлен в заголовочном файле `<thread>`.
* Конструктор класса принимает любое количество аргументов. Первый аргумент - функция, которую хотим вызвать. Остальные аргументы передаются в качестве аргументов вызова.
* Можно передать `std::ref`, чтобы избежать копирования.
* Обязательно потом вызвать `join`.
* Thread нельзя копировать.

## Класс `std::mutex`, `std::lock_guard`
* Mutex - защита совместно используемых различными нитями статических переменных. Он может быть заблокирован или разблокирован.
В статусе блокировки нельзя его повторно заблокировать. Разблокировать мьютекс обязана та же нить, которая его заблокировала.
* `Mutex` объявлен в заголовочном файле `<mutex>`.
Самые популярные методы класса:
```C++
void .lock() // блокирует mutex
void .unlock() // разблокирует mutex
bool .try_lock() // блокирует mutex, если это возможно
```
* Mutex опасен, когда принудительно выходим из-за return или exception и не успеваем разблокировать mutex.
* В стандартной библиотеке объявлен `std::lock_guard`, который разблокирует mutex вследствии удаления объекта `lock_guard`.

## Класс `std::future`
* [std::promise](https://en.cppreference.com/w/cpp/thread/promise) объявлен в заголовочном файле `<future>`.
* [std::future](https://en.cppreference.com/w/cpp/thread/future) объявлен в заголовочном файле `<future>`.
* `promise` и `future` нужны, чтобы получить возвращаемые значения функций. Они работают по аналогии с каналом. В `promise` пишем значения с помощью `.set_value(val)`, из `future` забираем с помощью `.get()`.
* Записать или получить значение можно только ОДИН раз. Повторный вызов приведет к выброса исключения.
* `future` и `promise` нельзя копировать.

## Класс `std::ref`, `std::cref`

* [std::ref/std::cref](https://en.cppreference.com/w/cpp/utility/functional/ref)
* нужны, чтобы не терять ссылку, когда передаем объект в поток
* создается объект [std::reference_wrapper](https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper), который можно недорого копировать и который умеет конвертироваться в ссылку. Таким образом можно по ссылке передавать аргументы в потоки.

## References
* [Прошлый год](https://github.com/blackav/hse-caos-2020/tree/master/23-stdthread)
* [Move-Семантика](https://github.com/blackav/hse-caos-2020/blob/master/23-stdthread/cxx11_move.md)
