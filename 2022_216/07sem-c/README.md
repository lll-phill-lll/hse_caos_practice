# 7 Семинар 10.01.2023 C динамическая память

## Файлики с кодом:
- [Бинарное дерево. Динамическая память. Указатели на функции.](tree.c)
- [Progress bar пользовательские настройки. Указатели на функции. Пользовательский контекст.](percentage_report_user.c)
- [Посимвольный ввод сравнение скорости.](input_perf/)

## ulimit:

`ulimit` используется для того, чтобы смотреть и менять ограничения shell сессии и запускаемых процессов.

Есть 2 лимита мягкий (S-soft) и жесткий (H-hard). Мягкий можно спокойно менять, но его
значение не может быть больше жесткого лимита. Жесткий можно спокойно уменьшать, но
увеличить уже нельзя без root прав. Например, есть ограничение на количество создаваемых
процессов `-u` или размер стека `-s`.

    ulimit -S -a - посмотреть мягкие ограничения на все ресурсы
    ulimit -H -a - посмотреть жесткие ограничения на все ресурсы
    ulimit -S -u - лимит на количество созданных процессов
    ulimit -S -s - размер стека
    ulimit -S -n - количество файловых дескрипторов

    ulimit -S -s 32 - установить мягкий лимит на размер стека в 32 Кб

    ulimit -S -u 1000 - установить soft limit на процессы запущенные пользователем
    ulimit -H -u 1000 - установить hard limit на процессы запущенные пользователем

Подробнее: `man limits.conf`

## Переполнение стека:

В коде задачи про дерево все обходы делаются рекурсивно, что плохо для стека.
Можно сымитировать переполонение стека руками.

Для этого понадобится утилита `ulimit`.

Проверим, сколько сейчас размер стека и запомним:

    ulimit -S -s

Установим мягкое ограничение размера стека в 32 Кб, как показано выше

    ulimit -S -s 32

запустим код с такими входными данными, чтобы дерево выродилось в одну длинную ветку:

    for i in `seq 1000`; do echo $i; done | ./a.out

То есть подадим на вход последовательные числа от 1 до 1000.

И наблюдаем, что начались сеголфолты. Это происходит из-за того, что стек переплонился.

Теперь вернем все как было (в моем случае изначальный размер стека был 8192):

    ulimit -S -s 8192

И если запустить опять, то все работает:

    for i in `seq 1000`; do echo $i; done | ./a.out


## valgrind:

Утечка памяти это серьезная проблема, которая может быть не сильно заметна
во время занятий. Но в жизни, если программа работает долго, отвечает на много запросов
и в ней есть утечка памяти, то рано или поздно память закончится и процесс умрет (например,
его убьет OOM-killer).

Для того чтобы проверить программу на утечки памяти, можно воспользоваться утилитой valgrind.

Он покажет, сколько памяти было аллоцировано и сколько освобождено. А если скомпилировать бинарь
с отладочными символами (с флагом `-g`), то valgrind покажет еще и строчку, где была выделена память,
которую потом не освободили.

    valgrind --leak-check=full ./a.out




## Стоимость malloc/calloc...:

Мы уже знаем, что системные вызовы делать долго, поэтому существует множество механизмов, которые позволяют
миинимизировать количество вызовов. Мы уже знаем, что буферизация помогает решить эту проблему для ввода и вывода.
Подробнее можно посмотреть [тут](input_perf/).

Динамическая память выделяется тоже операционной системой, поэтому, чтобы ее получить, необхоодимо сделать системный вызов.

Какой?

`man 3 malloc` говорит следующее:

    Normally, malloc() allocates memory from the heap, and adjusts the size of the heap  as  required,  using  sbrk(2).   When  allocating  blocks  of  memory  larger  than
    MMAP_THRESHOLD  bytes, the glibc malloc() implementation allocates the memory as a private anonymous mapping using mmap(2).  MMAP_THRESHOLD is 128 kB by default, but is
    adjustable using mallopt(3).

Значит для небольших аллокаций используется `sbrk`, а для больших `mmap`. Посмотрим, как часто и какие аллокации будет делать наше дерево.
Если грубо, то у нас должно быть по 3 небольшие аллокации на каждую ноду: строка и 2 ребенка.

Посмотреть, как работает `brk/sbrk` можно в `man 2 brk`.

Посмотрим, сколько раз вызовется `brk` в дереве. Положим 100 случайных чисел
дерево и в `strace` посмотрим, сколько раз был сделан системный вызов `brk`.

    for i in `seq 100`; do echo $RANDOM; done | strace ./a.out 2>&1 | grep brk

Результат:

    brk(NULL)                               = 0x5584a3c4d000
    brk(NULL)                               = 0x5584a3c4d000
    brk(0x5584a3c6e000)                     = 0x5584a3c6e000

При этом 2 раза вызывается с аргументом `NULL` (это делается для того, чтобы
узнать адрес начала кучи (системный вызов `brk` в отличие от обертки из glibc
возвращает адрес конца кучи после увеличения), поэтому передавая в него `NULL` можно узнать адрес начала.

Заметим, что количество вызовов отличается от грубой оценки `3 * 100`.
Таким образом как раз malloc и минимизирует количество системных вызовов:
**сразу запрашивает больше памяти, чем нужно, чтобы при следующих аллокациях
не обращаться к операционной системе, а использовать уже выделенную память.**

Попробуем увеличить количество элементов в дереве:

    for i in `seq 10000`; do echo $RANDOM; done | strace ./a.out 2>&1 | grep brk

Результат:

    brk(NULL)                               = 0x55a81e0cf000
    brk(NULL)                               = 0x55a81e0cf000
    brk(0x55a81e0f0000)                     = 0x55a81e0f0000
    brk(0x55a81e111000)                     = 0x55a81e111000
    brk(0x55a81e132000)                     = 0x55a81e132000

Увеличим еще:

    for i in `seq 10000`; do echo $RANDOM; done | strace ./a.out 2>&1 | grep brk

Результат:

    brk(NULL)                               = 0x55d519fdf000
    brk(NULL)                               = 0x55d519fdf000
    brk(0x55d51a000000)                     = 0x55d51a000000
    brk(0x55d51a021000)                     = 0x55d51a021000
    brk(0x55d51a042000)                     = 0x55d51a042000
    brk(0x55d51a063000)                     = 0x55d51a063000
    brk(0x55d51a084000)                     = 0x55d51a084000
    brk(0x55d51a0a5000)                     = 0x55d51a0a5000
    brk(0x55d51a0c6000)                     = 0x55d51a0c6000
    brk(0x55d51a0e7000)                     = 0x55d51a0e7000
    brk(0x55d51a108000)                     = 0x55d51a108000
    brk(0x55d51a129000)                     = 0x55d51a129000
    brk(0x55d51a14a000)                     = 0x55d51a14a000
    brk(0x55d51a16b000)                     = 0x55d51a16b000
    brk(0x55d51a18c000)                     = 0x55d51a18c000
    brk(0x55d51a1ad000)                     = 0x55d51a1ad000
    brk(0x55d51a1ce000)                     = 0x55d51a1ce000
    brk(0x55d51a1ef000)                     = 0x55d51a1ef000
    brk(0x55d51a210000)                     = 0x55d51a210000
    brk(0x55d51a231000)                     = 0x55d51a231000
    brk(0x55d51a252000)                     = 0x55d51a252000
    brk(0x55d51a273000)                     = 0x55d51a273000
    brk(0x55d51a294000)                     = 0x55d51a294000
    brk(0x55d51a2b5000)                     = 0x55d51a2b5000
    brk(0x55d51a2d6000)                     = 0x55d51a2d6000
    brk(0x55d51a2f7000)                     = 0x55d51a2f7000

Попробуем теперь сделать следующее. Будем создавать не одно большое дерево, а много маленьких. Для этого добавим в код удааление дерева при достижении
им размера 1000.

Добавим к код:

    if (counter % 1000 == 0) {
        delete(tree);
        tree = NULL;
    }

В таком случае количество вызовов уже куда меньше:

    brk(NULL)                               = 0x55b28d901000
    brk(NULL)                               = 0x55b28d901000
    brk(0x55b28d922000)                     = 0x55b28d922000
    brk(0x55b28d943000)                     = 0x55b28d943000
    brk(0x55b28d964000)                     = 0x55b28d964000

Таким образом мы можем видеть еще одну особенность работы malloc: **он может
переиспользовать память, которая уже была освобождена.** Как мы видим,
адреса, с которыми вызывался `brk` не уменьшались, а значит память при удалении
дерева не возвращалась операциоонной системе, и `malloc` мог ее переиспользоовать
для построения других деревьев.


## Notes:

1. Нельзя 2 раза делать `free` - это UB.
2. Можно делать `free(NULL)`.
3. `free` не меняет значение указателя на `NULL`. Нет способа проверить, освобождена ли память по указателю.
Поэтому для удобства можно после `free(ptr)` делать `ptr = NULL`.
4. Между `malloc` и `calloc` лучше выбирать `calloc`. Во-первых, есть шанс, что зануленная память нам достанется бесплатно
(возьмутся оболасти памяти, которые уже занулены) и не надо будет делать `memset`. Во-вторых, при умножении `size * amount` в `malloc`
может произойти переполонение и мы об этом не узнаем. Тогда как `calloc` принимает 2 аргумента и сам их перемножает и в случае
переполнения не выделит память и мы об этом узнаем через возвращаемое значение.
