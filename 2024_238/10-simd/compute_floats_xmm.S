    .intel_syntax noprefix
    .global process

// (a + b) / (c + (float)d)
process:
    push    rbp
    mov     rbp, rsp

    // xmm0 = a, xmm1 = b, xmm2 = c, rdi = d

    // add s - scalar s - single(float)
    addss   xmm0, xmm1                   // xmm0 = a + b

    cvtsi2ss xmm3, rdi                   // xmm3 = (float)d
    addss   xmm2, xmm3                   // xmm2 = c + (float)d

    // Деление (a + b) / (c + float(d))
    divss   xmm0, xmm2
    // cvtss2sd xmm0, xmm0
    // lea     rdi, [rip + printf_format]
    // mov     rax, 1
    // call    printf

    mov     rsp, rbp
    pop     rbp
    ret

printf_format:
    .string     "%f\n"
