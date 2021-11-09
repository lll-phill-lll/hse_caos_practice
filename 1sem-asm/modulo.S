// остаток от деления
// посмотреть в gdb,
// что происходит с числами
    .global main
main:
    call readi32
    mov %eax, %ebx

    call readi32

    sub $1, %eax

    and %ebx, %eax

    call writei32
    call finish
