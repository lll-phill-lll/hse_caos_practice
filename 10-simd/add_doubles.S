    .intel_syntax noprefix
    .global main

main:
    push    rbp
    mov     rbp, rsp

    movsd   xmm0, [rip + x]
    movsd   xmm1, [rip + y]

    addsd   xmm0, xmm1                   

    lea     rdi, [rip + printf_format]
    mov     rax, 1
    call    printf

    mov     rsp, rbp
    pop     rbp
    ret

    .data
x:
    .double    3.1
y:
    .double    4.2

printf_format:
    .string    "%f\n"
