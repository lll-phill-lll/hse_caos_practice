    .text
    .global main
main:
    push    %ebp
    mov     %esp, %ebp

    movsd   x, %xmm0
    movsd   y, %xmm1

    addsd   %xmm1, %xmm0

    sub     $8, %esp
    movsd   %xmm0, (%esp)
    push    $printf_format

    call    printf

    mov     %ebp, %esp
    pop     %ebp

    .data
x:
    .double    3.1
y:
    .double    4.2


printf_format:
    .string "%f\n"
