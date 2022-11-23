// Task: read a number from input. Write 1 if number if even, 0 otherwise.

    .global main
main:
    call    readi32

    test    $1, %eax
    jz      even

    xor     %eax, %eax
    jmp     fin

even:
    mov     $1, %eax

fin:
    call    writei32
    call    finish
