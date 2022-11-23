    .global main
main:
    call    readi32
    test    $1, %eax
    jz      even

    mov     $0, %eax
    jmp     fin

even:
    mov     $1, %eax

fin:
    call    writei32
    call    finish
