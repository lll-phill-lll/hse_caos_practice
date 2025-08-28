    // (a + b) / (c + d)

    .text
    .global main
main:
    push    %ebp
    mov     %esp, %ebp

    fld     a // st(0) -> a
    fadd    b // st(0) -> a + b

    fild    d // st(0)
    fadd    c
    // st(0) st(1)

    // st(1) / st(0) -> st(0)
    fdivrp  %st(0), %st(1)

    sub     $8, %esp
    fstpl   (%esp)


    push    $printf_format

    call    printf

    mov     %ebp, %esp
    pop     %ebp

    .data
a:
    .float    1.1
b:
    .float    2.2
c:
    .float    3.3
d:
    .int       4



printf_format:
    .string "%f\n"
