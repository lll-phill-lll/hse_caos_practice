// Посмотреть в gdb, что произошло с %eax, %edx после cdq
    .global main
main:
    call readi32
    cdq

    call finish
