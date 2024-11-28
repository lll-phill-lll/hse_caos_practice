    .intel_syntax noprefix

.global dot_product

dot_product:
    push    rbp
    mov     rbp, rsp

    // rdi = n
    // rsi = vec1
    // rdx = vec2

    xor     r8, r8                  // r8 = counter
    xorpd   xmm0, xmm0              // xmm0 = результат

for_loop:
    cmp     r8, rdi                 // Если r8 >= n -> выходим
    jae     end_loop

    // xm1 = vec1[r8]
    movsd   xmm1, qword ptr [rsi + r8 * 8]

    // xmm2 = vec2[r8]
    movsd   xmm2, qword ptr [rdx + r8 * 8]

    // xmm1 = vec1[r8] * vec2[r8]
    mulsd   xmm1, xmm2

    // xmm0 += xmm1
    addsd   xmm0, xmm1

    inc     r8
    jmp     for_loop

end_loop:
    mov     rsp, rbp
    pop     rbp
    ret

