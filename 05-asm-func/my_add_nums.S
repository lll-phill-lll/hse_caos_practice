.global my_add_nums

my_add_nums:
    // ---------------
    push    %ebp
    mov     %esp, %ebp
    // ---------------

    // %ecx - counter (number of args)
    mov     8(%ebp), %ecx
    // %edx - address of argument
    lea     8(%ebp), %edx

    xor     %eax, %eax

cycle:

    // go to the next argument
    add     $4, %edx
    add     (%edx), %eax

    loop    cycle

    // ---------------
    mov     %esp, %ebp
    pop     %ebp
    // ---------------

    ret
