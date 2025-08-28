    .intel_syntax noprefix
.global dot_product_vec

dot_product_vec:
    push    rbp
    mov     rbp, rsp

    // rdi = n
    // rsi = vec1
    // rdx = vec2

    xorpd   xmm0, xmm0              // xmm0 = результат

for_loop:
    cmp     rdi, 2                  // Если n < 2, обрабатываем последний элемент
    jl      process_last

    movupd  xmm1, [rsi]             // xmm1 = vec1[n], vec1[n-1]

    movupd  xmm2, [rdx]             // xmm2 = vec2[n], vec2[n-1]

    mulpd   xmm1, xmm2              // xmm1 = vec1 * vec2

    addpd   xmm0, xmm1              // xmm0 += vec1 * vec2

    // Переходим к следующему элементу
    add     rsi, 16
    add     rdx, 16
    sub     rdi, 2
    jmp     for_loop

process_last:
    haddpd  xmm0, xmm0              // xmm0[0] = xmm0[0] + xmm0[1]

    //  Дообработаем последний элемент
    cmp     rdi, 1
    jne     fin

    movsd   xmm1, qword ptr [rsi]   // xmm1 = vec1[0]
    movsd   xmm2, qword ptr [rdx]   // xmm2 = vec2[0]

    mulsd   xmm1, xmm2              // xmm1 = vec1[0] * vec2[0]
    addsd   xmm0, xmm1              // xmm0 += xmm1

fin:
    mov     rsp, rbp
    pop     rbp
    ret

