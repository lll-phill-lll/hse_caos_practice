    .global main
main:
    call    readi32
loop:
    add     $1, %eax
    call    writei32
    mov     %eax, %ebx
    sub     $1000, %ebx // %ebx = %ebx - 1000
    jz      fin // %ebx ?= 0

    jmp     loop

fin:
    call    finish
