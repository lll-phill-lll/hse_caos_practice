// Простое использование переменной
    .global main
main:
    mov     var, %eax
    call    writei32

    call    finish

var:
    .int    42
