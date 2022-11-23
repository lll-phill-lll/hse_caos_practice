# АКОС (архитектура компьютеров и операционные системы)

# Страничка семинаров 207 группы

## Навигация по семинарам
1.  [[видео](https://www.youtube.com/watch?v=Tutix99Y2_I)][[конспект](01sem-asm)][asm] - введение в ассемблер
2.  [[видео](https://www.youtube.com/watch?v=1aZq5COiZks)][[конспект](02sem-asm)][asm] - работа со стеком, вызов фуннкций из C/C++ кода
3.  [[видео](https://www.youtube.com/watch?v=Ty-TfSRB2P8)][[конспект](03sem-asm)][asm] - работа со строками, системные вызовы, локальные переменные
4.  [[видео](https://www.youtube.com/watch?v=oqwXGwMW16o)][[конспект](04sem-asm)][asm] - работа с кучей. Системный вызов brk. my_malloc/my_free
5.  [[видео](https://www.youtube.com/watch?v=YPteBhvUSWg)][[конспект](05sem-c)][c]     - printf/scanf, выравнивание
6.  [[видео](https://www.youtube.com/watch?v=rGtolk1oupY)][[конспект](06sem-c)][c]     - работа с файлами, буферизация
7.  [[видео](https://www.youtube.com/watch?v=XGcy3BW0k_w)][[конспект](07sem-c)][c]     - переполнение буфера, кэш при умножении матриц
8.  [[видео](https://www.youtube.com/watch?v=F_4nqZTy8Ac)][[конспект](08sem-c)][c]     - float/double, union для получение частей float
9.  [[видео](https://www.youtube.com/watch?v=0hi7nVjlPcQ)][[конспект](09sem-asm)][asm] - векторизованные операции. XMM регистры, inline asm
10. [[видео](https://www.youtube.com/watch?v=V7PXDmYebl8)][[конспект](10sem-fs)][fs]   - права доступа. симлинки. работа с файлами и директориями
11. [[видео](https://www.youtube.com/watch?v=8i77sve9QWk)][[конспект](11sem-fs)][fs]   - mmap, fork, fork bomb, limits
12. [[видео](https://www.youtube.com/watch?v=A1nsJdVrJq8)][[конспект](12sem-fs)][fs]   - fork
13. [[видео](https://www.youtube.com/watch?v=ohPIf5DLeHk)][[конспект](13sem-fs)][fs]   - переменные окружения, exec
14. [[видео](https://www.youtube.com/watch?v=h1b9DMZH8uU)][[конспект](14sem-fs)][fs]   - dup, dup2, pipe, dup2+pipe+fork
15. [[видео](https://www.youtube.com/watch?v=gBL-03voBZM)][[конспект](15sem-fs)][fs]   - сигналы, sigaction
16. [[видео](https://www.youtube.com/watch?v=-iNalmZUe-g)][[конспект](16sem-fs)][fs]   - сигналы 2
17. [[видео](https://www.youtube.com/watch?v=SvhKXFCBRA4)][[конспект](17sem-fs)][fs]   - время, mktime, gettimeofday, 2038 год, localtime
18. [[видео](https://www.youtube.com/watch?v=pWPCKwtP9Mc)][[конспект](18sem-fs)][fs]   - файловые дескрипторы: eventfd, signalfd, timerfd
19. [[видео](https://www.youtube.com/watch?v=wHJIWjxMAoM)][[конспект](19sem-fs)][fs]   - epoll, select, timer,
20. [[видео](https://www.youtube.com/watch?v=0Oc4tIm2Y7E)][[конспект](20sem-fs)][fs]   - сокеты, getaddrinfo, socket+epoll

## Навигация по темам

* [Компиляция с simpleio](01sem-asm#%D0%BA%D0%BE%D0%BC%D0%BF%D0%B8%D0%BB%D1%8F%D1%86%D0%B8%D1%8F)
* [Gdb](01sem-asm#gdb)
* [Регистры и флаги](01sem-asm#%D1%80%D0%B5%D0%B3%D0%B8%D1%81%D1%82%D1%80%D1%8B)
* [Соглашение о вызовах cdecl](02sem-asm#%D1%81%D0%BE%D0%B3%D0%BB%D0%B0%D1%88%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BE-%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2%D1%8B%D1%85-cdecl32-%D0%B1%D0%B8%D1%82%D0%B0)
* [Использование c/cpp кода](02sem-asm#%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0-%D1%81-c-%D0%B8-c-%D0%BA%D0%BE%D0%B4%D0%BE%D0%BC)
* [Стек](02sem-asm#%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0-%D1%81%D0%BE-%D1%81%D1%82%D0%B5%D0%BA%D0%BE%D0%BC-tbd)
* [Системный вызов из ассемблера](03sem-asm#%D1%81%D0%B4%D0%B5%D0%BB%D0%B0%D1%82%D1%8C-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%BD%D1%8B%D0%B9-%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2)
* [stdout/stderr](03sem-asm#%D0%BF%D0%BE%D1%81%D0%BC%D0%BE%D1%82%D1%80%D0%B5%D1%82%D1%8C-%D0%BA%D0%B0%D0%BA-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0%D1%8E%D1%82-stdoutstderr)
* [lea для арифметики](03sem-asm#lea)
* [brk](04sem-asm#системный-вызов-brk)
* [Посимвольное чтение из файла](06sem-c/input_perf)
* [Прогресс бар](06sem-c/progress.c)
* [Уязвимость с перепоолнением буфера](07sem-c/test_overflow.c)
* [float IEEE-754](08sem-c#%D0%BF%D1%80%D0%B5%D0%B4%D1%81%D1%82%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2%D0%B5%D1%89%D0%B5%D1%81%D1%82%D0%B2%D0%B5%D0%BD%D0%BD%D1%8B%D1%85-%D1%87%D0%B8%D1%81%D0%B5%D0%BB)
* [union для float](08sem-c/float_parts.c)
* [ulimit](11sem-fs#ulimit)

## Файлы

* [C11 стандарт](C11_standard.pdf)
