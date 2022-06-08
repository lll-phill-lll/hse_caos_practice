 # 23 Семинар 31.06.2022 Threads, atomic

## Файлики с кодом:

* [Создаем простой банк](bank_add_simple.c)
* [Добавляем потоков](bank_add_threads.c)
* [Работа с pipe](pipe_simple.c)
* [pipe & fork](pipe_fork.c)
* [невероятный пример](full_example.c)
* [механика второго примера](program.c)


#  dup/dup2
```
#include <unistd.h>

int dup(int old_fd);
int dup2(int old_fd, int new_fd);
```

dup() создает новый независимый файловый дискриптор, который указывает на тот же файл. 

dup2(old_fd, new_fd) - заменяет один файловый дискриптор другим.

Возвращают -1, если что-то пошло не так.
