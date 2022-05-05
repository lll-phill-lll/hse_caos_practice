        .data
        .text
        .global dot_product_vec

dot_product_vec:
        push    %ebp
        mov     %esp, %ebp

        push    %esi
        push    %ebx

        mov     8(%ebp), %eax   //int
        mov     12(%ebp), %ebx  // double pointer
        mov     16(%ebp), %edx  // double pointer

        xorpd   %xmm2, %xmm2

for:
        cmp     $2, %eax
        jl      process_last

        movupd  (%ebx), %xmm0
        movupd  (%edx), %xmm1
        mulpd   %xmm1, %xmm0
        addpd   %xmm0, %xmm2

        add     $16, %ebx
        add     $16, %edx
        sub     $2, %eax
        jmp     for

process_last:
        haddpd  %xmm2, %xmm2
        cmp     $1, %eax
        jne     fin

        movsd  (%ebx), %xmm0
        movsd  (%edx), %xmm1
        mulsd   %xmm1, %xmm0
        addsd   %xmm0, %xmm2

fin:
        sub     $8, %esp
        movsd   %xmm2, (%esp)
        fldl    (%esp)
        add     $8, %esp


        pop     %ebx
        pop     %esi
        mov     %ebp, %esp
        pop     %ebp
        ret
