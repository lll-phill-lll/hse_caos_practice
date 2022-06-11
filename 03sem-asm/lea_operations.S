// **Условие**
// Посмотреть, как работает арифметика с командой lea

    .global main
main:
    mov     $5, %ecx
    mov     $6, %edx

    // lea offset(base, index, mult), reg -> offset + base + index * mult -> reg
    // lea не сохраняет промежуточные результаты и не выставляет флаги
    
    //      2 + (6)
    lea     2(%edx), %eax
    call    writei32
    
    //      -3 + (6)
    lea     -3(%edx), %eax
    call    writei32

    //      (5 + 6)
    lea     (%ecx, %edx), %eax
    call    writei32

    //      4 + (5 + 6)
    lea     4(%ecx, %edx), %eax
    call    writei32

    //      4 + (6)
    lea     4(, %edx), %eax
    call    writei32

    //      4 + (5 + 6 * 2)
    lea     4(%ecx, %edx, 2), %eax
    call    writei32

    // only 1, 2, 4, 8
    // lea     (, %edx, 3), %eax
    // call    writei32

    // Хак с умножением на 3 и на 5
    //      (6 + 6 * 2)
    lea     (%edx, %edx, 2), %eax
    call    writei32

    //      12 + (6 + 6 * 2)
    lea     12(%edx, %edx, 2), %eax
    call    writei32
    
    //      (6 + 6 * 4)
    lea     (%edx, %edx, 4), %eax
    call    writei32

    call    finish
