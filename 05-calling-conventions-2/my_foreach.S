    // extern "C" void my_for_each(int* arr, int size, int (*modifier)(int*));
    .intel_syntax noprefix
    .global my_for_each

my_for_each:
    push    rbp
    mov     rbp, rsp
    push    r12
    push    r13
    push    r14
    push    r15

    mov     r12, rdi    // int* arr
    mov     r13, rsi    // int size
    mov     r14, rdx    // int (*modifier)(int*)

cycle:
    mov     rdi, r12
    call    r14           // Вызываем функцию модификации

    add     r12, 4        // Переходим к следующему элементу (int = 4 байта)


    dec     r13
    jnz     cycle


    pop     r15
    pop     r14
    pop     r13
    pop     r12
    mov     rsp, rbp
    pop     rbp
    ret

