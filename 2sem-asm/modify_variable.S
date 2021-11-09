    .global main
main:

    // mov x, y not alloved
    mov x, %eax
    mov %eax, y

    mov y, %eax
    call writei32
    call finish

    .data
x:
    .int 42
y:
    .int 50
