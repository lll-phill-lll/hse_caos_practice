// new note
.data
        .text
        .global myhypot

myhypot:
        push    %ebp
        mov     %esp, %ebp

        movsd   8(%ebp), %xmm0
        movsd   16(%ebp), %xmm1

        mulsd   %xmm0, %xmm0
        mulsd   %xmm1, %xmm1
        addsd   %xmm1, %xmm0
        sqrtsd  %xmm0, %xmm0

        mov     24(%ebp), %eax
        movsd   %xmm0, (%eax)

        mov     %ebp, %esp
        pop     %ebp
        ret
