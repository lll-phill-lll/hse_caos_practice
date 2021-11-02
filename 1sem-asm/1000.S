//  пример кода с лекции
    .global main
main:
    mov $0, %eax
    call writei32
loop:
    add $1, %eax
    call writei32
    mov %eax, %ebx
    sub $1000, %ebx
    jz fin

    jmp loop

fin:
    call finish
