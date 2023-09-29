.global count_digits

count_digits:
    push    %ebp
    mov     %esp, %ebp

    mov     8(%ebp), %edx

    xor     %eax, %eax

cycle:
    cmpb    $0, (%edx)
    je      fin

    cmpb    $'0', (%edx)
    jl      increment

    cmpb    $'9', (%edx)
    jg      increment

    xor     %ecx, %ecx
    movb    (%edx), %cl
    subb    $'0', %cl
    add     %ecx, %eax

increment:

    incl    %edx
    jmp     cycle

fin:
    mov     %esp, %ebp
    pop     %ebp


    ret


