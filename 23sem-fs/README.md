 # 23 Семинар 31.06.2022 Threads, atomic

## Файлики с кодом:

* [Создаем простой банк](bank_add_simple.c)
* [Добавляем потоков](bank_add_threads.c)
* [Работа с pipe](pipe_simple.c)
* [pipe & fork](pipe_fork.c)
* [невероятный пример](full_example.c)
* [механика второго примера](program.c)


#  threads
```
int balance;
balance += amount;
```
|основной код лежит в [файле](bank_add_threads.c)|
при множестве операций возникнет data race, в следствии получаем UB, потому что процессы начинают вклиниваться и мешать друг другу

#  threads + atomic
```
_Atomic int balance;
balance += amount;
```
|основной код лежит в [файле](bank_add_threads.c)|
делаем переменную атомарной, тем самым обеспечив гарантию того, что все операции над переменной проходят последовательно и не прерываются

#  threads + atomic функции
```
int balance;
atomic_fetch_add(&account->balance, amount);
```
|основной код лежит в [файле](bank_add_threads.c)|
делаем операции атомарными, значит сами операции выполняются последовательно и не прерываются



