#include <sys/syscall.h>

    .global _start
_start:
    // Системный вызов brk вернет адрес конца памяти (отличается от возвращаемого значения,
    // написанного в man 2 brk, так как в мане описана обертка над систенмым вызовом), которую мы запросили.
    // Память выделяется в куче.
    // Если мы сделаем вызов brk с аргументом 0, то получим адрес начала 
    // и одновременно конца доступной области памяти.
    mov     $SYS_brk, %eax
    mov     $0, %ebx
    int     $0x80

    // Сохраним полученый адрес начала кучи в heapstart
    mov     %eax, heapstart

    mov     %eax, %edx
    // Если попробуем что-то записать по этому адресу, то получим segfault.
    // Поскольку мы не просили ничего нам выделить
    // movl    $42, (%edx)

    // В brk нужно передать адрес конца памяти, до куда мы хотим ее выделить.
    // Выделим 1 МБ. Прибавим 2**20 к eax (в котором лежит сейчас адрес начала кучи)
    add     $1<<20, %eax
    // Переложим в ebx для того, чтобы сделать системный вызов
    mov     %eax, %ebx

    // Просим выделить нам память от heapstart до heapstart + 1<<20
    mov     $SYS_brk, %eax
    int     $0x80

    // Сохраним полученный адрес в heapend
    mov     %eax, heapend

    // Теперь уже не будет segfault поскольку память выделена
    // и мы можем туда что-то сложить
    // movl    $42, (%edx)

    mov     $SYS_exit, %eax
    mov     $0, %ebx
    int     $0x80

    .data
// Адрес начала кучи
heapstart:
    .int 0
// Адрес конца кучи
heapend:
    .int 0
