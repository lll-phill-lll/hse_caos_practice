// **Условие**
// Посмотреть, как работает арифметика с командой lea

    .global main
main:
    mov     $5, %ecx
    mov     $6, %edx

    // lea offset(base, index, mult), reg -> offset + base + index * mult -> reg
    // lea не сохраняет промежуточные результаты и не выставляет флаги
    // в качестве mult можно использовать 1, 2, 4, 8

    // eax = 2 + edx
    lea     2(%edx), %eax
    call    writei32

    // eax = -3 + edx
    lea     -3(%edx), %eax
    call    writei32

    // eax = ecx + edx
    lea     (%ecx, %edx), %eax
    call    writei32

    // eax = 4 + ecx + edx
    lea     4(%ecx, %edx), %eax
    call    writei32

    // eax = 4 + edx
    lea     4(, %edx), %eax
    call    writei32

    // eax = 4 + ecx + edx * 2
    lea     4(%ecx, %edx, 2), %eax
    call    writei32

    // в качестве множителя могут быть только 1 2 3 4 8
    // // lea     (, %edx, 3), %eax
    // // call    writei32

    // eax = edx + edx * 2 = edx * 3
    lea     (%edx, %edx, 2), %eax
    call    writei32

    // eax = 12 + edx + edx * 2
    lea     12(%edx, %edx, 2), %eax
    call    writei32

    // eax = edx + edx * 4
    lea     (%edx, %edx, 4), %eax
    call    writei32

    call    finish
