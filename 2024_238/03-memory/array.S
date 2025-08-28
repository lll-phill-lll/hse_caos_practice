    .intel_syntax noprefix
    .global main
main:
    call    readi64         // прочитали индекс
    jc      fin
    // r12 - индекс
    mov     r12, rax


    call    readi64         // читаем новое значение
    jc      fin
    // r13 - новое значение
    mov     r13, rax

    // BREG + IREG * SCALE + OFFSET
    // SCALE = 1, 2, 4, 8

    lea     r14, [rip + arr]        // абсолютный адрес массива
    lea     r14, [r14 + 8 * r12]    // абсолютный адрес ячейки

    mov     rdi, [r14]

    call    writei64

    mov     [r14], r13
    // r14 = 0x3724621374

    jmp     main

fin:
    call    finish

    .bss
arr:
    .skip 200 * 8               // 200 8-байтных чисел
