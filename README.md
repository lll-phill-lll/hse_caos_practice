# АКОС (архитектура компьютеров и операционные системы)

# Страничка семинаров 207 группы

## Навигация по семинарам
1.  [[видео](https://www.youtube.com/watch?v=Tutix99Y2_I)][[конспект](1sem-asm)][asm] - введение в ассемблер
2.  [[видео](https://www.youtube.com/watch?v=1aZq5COiZks)][[конспект](2sem-asm)][asm] - работа со стеком, вызов фуннкций из C/C++ кода
3.  [[видео](https://www.youtube.com/watch?v=Ty-TfSRB2P8)][[конспект](3sem-asm)][asm] - работа со строками, системные вызовы, локальные переменные
4.  [[видео](https://www.youtube.com/watch?v=oqwXGwMW16o)][[конспект](4sem-asm)][asm] - работа с кучей. Системный вызов brk. my_malloc/my_free
5.  [[видео](https://www.youtube.com/watch?v=YPteBhvUSWg)][[конспект](5sem-c)][c]     - printf/scanf, выравнивание
6.  [[видео](https://www.youtube.com/watch?v=rGtolk1oupY)][[конспект](6sem-c)][c]     - работа с файлами, буферизация
7.  [[видео](https://www.youtube.com/watch?v=XGcy3BW0k_w)][[конспект](7sem-c)][c]     - переполнение буфера, кэш при умножении матриц
8.  [видео][[конспект](8sem-c)][c]                                                    - float/double, union для получение частей float
9.  [[видео](https://www.youtube.com/watch?v=0hi7nVjlPcQ)][[конспект](9sem-asm)][asm] - векторизованные операции. XMM регистры, inline asm
10. [[видео](https://www.youtube.com/watch?v=V7PXDmYebl8)][[конспект](10sem-fs)][fs]  - права доступа. симлинки. работа с файлами и директориями
11. [[видео](https://www.youtube.com/watch?v=8i77sve9QWk)][[конспект](11sem-fs)][fs]  - mmap, fork, fork bomb, limits
12. [[видео](https://www.youtube.com/watch?v=A1nsJdVrJq8)][[конспект](12sem-fs)][fs]  - fork
13. [[видео](https://www.youtube.com/watch?v=ohPIf5DLeHk)][[конспект](13sem-fs)][fs]  - переменные окружения, exec

## Навигация по темам

* [Компиляция с simpleio](1sem-asm#%D0%BA%D0%BE%D0%BC%D0%BF%D0%B8%D0%BB%D1%8F%D1%86%D0%B8%D1%8F)
* [Gdb](1sem-asm#gdb)
* [Регистры и флаги](1sem-asm#%D1%80%D0%B5%D0%B3%D0%B8%D1%81%D1%82%D1%80%D1%8B)
* [Соглашение о вызовах cdecl](2sem-asm#%D1%81%D0%BE%D0%B3%D0%BB%D0%B0%D1%88%D0%B5%D0%BD%D0%B8%D0%B5-%D0%BE-%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2%D1%8B%D1%85-cdecl32-%D0%B1%D0%B8%D1%82%D0%B0)
* [Использование c/cpp кода](2sem-asm#%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0-%D1%81-c-%D0%B8-c-%D0%BA%D0%BE%D0%B4%D0%BE%D0%BC)
* [Стек](2sem-asm#%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0-%D1%81%D0%BE-%D1%81%D1%82%D0%B5%D0%BA%D0%BE%D0%BC-tbd)
* [Системный вызов из ассемблера](3sem-asm#%D1%81%D0%B4%D0%B5%D0%BB%D0%B0%D1%82%D1%8C-%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D0%BD%D1%8B%D0%B9-%D0%B2%D1%8B%D0%B7%D0%BE%D0%B2)
* [stdout/stderr](3sem-asm#%D0%BF%D0%BE%D1%81%D0%BC%D0%BE%D1%82%D1%80%D0%B5%D1%82%D1%8C-%D0%BA%D0%B0%D0%BA-%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0%D1%8E%D1%82-stdoutstderr)
* [lea для арифметики](3sem-asm#lea)
* [brk](4sem-asm#системный-вызов-brk)
* [Посимвольное чтение из файла](6sem-c/input_perf)
* [Прогресс бар](6sem-c/progress.c)
* [Уязвимость с перепоолнением буфера](7sem-c/test_overflow.c)
* [float IEEE-754](8sem-c#%D0%BF%D1%80%D0%B5%D0%B4%D1%81%D1%82%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2%D0%B5%D1%89%D0%B5%D1%81%D1%82%D0%B2%D0%B5%D0%BD%D0%BD%D1%8B%D1%85-%D1%87%D0%B8%D1%81%D0%B5%D0%BB)
* [union для float](8sem-c/float_parts.c)
* [ulimit](11sem-fs#ulimit)

## Файлы

* [C11 стандарт](C11_standard.pdf)
