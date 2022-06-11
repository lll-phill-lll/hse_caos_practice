        .data
        .text
        .global dot_product

dot_product:
        push    %ebp
        mov     %esp, %ebp

        push    %esi
        push    %ebx

        mov     8(%ebp), %eax   //int
        mov     12(%ebp), %ebx  // double pointer
        mov     16(%ebp), %edx  // double pointer

        // esi - counter
        mov     $0, %esi
        // xmm2 - result
        xorpd   %xmm2, %xmm2

for:
        cmpl    %eax, %esi
        je      fin

        // 1st double array
        movsd   (%ebx), %xmm0
        // 2st double array
        movsd   (%edx), %xmm1
        mulsd   %xmm1, %xmm0
        addsd   %xmm0, %xmm2

        addl    $8, %ebx
        addl    $8, %edx
        decl    %eax
        jmp     for
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
