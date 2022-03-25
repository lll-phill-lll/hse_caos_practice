# 14 Семинар 01.03.2022 dup/dup2/pipe/dup2+pipe+fork

## Файлики с кодом:

* [Примеры работы dup/dup2](dup.c)
* [что-то еще](dup_fork.c)
* [что-то еще](full_example.c)
* [что-то еще](pipe_fork.c)
* [что-то еще](pipe_simple.c)
* [что-то еще](program.c)


#  dup/dup2
```
#include <unistd.h>

int dup(int old_fd);
int dup2(int old_fd, int new_fd);
```

dup() создает новый независимый файловый дискриптор, который указывает на тот же файл.
dup2(old_fd, new_fd) - заменяет один файловый дискриптор другим.








