// Посмотреть в gdb на %eax, %edx после 1 и второго чтения
    .global main
main:
    call readi32
    call readi64
    call finish

