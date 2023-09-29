
.global compute_hypots

compute_hypots:

    push    %ebp
    mov     %esp, %ebp

    push    %ebx

    mov     8(%ebp), %edx
    mov     12(%ebp), %ecx

compute:

    mov     (%edx), %eax
    imull   %eax, %eax

    mov     4(%edx), %ebx
    imull   %ebx, %ebx

    add     %ebx, %eax

    movl    %eax, 8(%edx)

    add     $12, %edx
    loop    compute

    pop     %ebx

    mov     %ebp, %esp
    pop     %ebp


    ret
