
    .intel_syntax noprefix
    .global process

// (a + b) / (c + (float)d)
process:
    push    rbp
    mov     rbp, rsp

    sub     rsp, 32
    movss   [rbp - 8], xmm0              // a
    movss   [rbp - 16], xmm1             // b
    mov     [rbp - 24], rdi              // d
    movss   [rbp - 32], xmm2             // c

    fld     dword ptr [rbp - 8]          // ST(0) = a
    fadd    dword ptr [rbp - 16]         // ST(0) = a + b

    fild    dword ptr [rbp - 24]         // ST(0) = float(d), ST(1) = a + b
    fadd    dword ptr [rbp - 32]         // ST(0) = c + float(d)

    fdivp                                // ST(0) = (a + b) / (c + float(d))

    fstp    dword ptr [rbp - 8]          // Сохраняем результат на стек
    movss   xmm0, dword ptr [rbp - 8]    // Загружаем результат в xmm0

    mov     rsp, rbp
    pop     rbp
    ret
