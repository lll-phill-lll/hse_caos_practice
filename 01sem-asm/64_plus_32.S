// прочитать 64 битное число и 32 битное и вывести сумму
// В случае знакового переполнения вывести -1. Если не полоучилось считать
// вывести 0
    .global main
main:
    call readi64
    jc fail
    mov %eax, %ebx
    mov %edx, %ecx
    call readi32
    jc fail
    cdq
    add %ebx, %eax
    adc %ecx, %edx
    jo overflow
    call writei64
    call finish
fail:
    xor %eax, %eax
    call writei32
    call finish
overflow:
    mov $-1, %eax
    call writei32
    call finish
