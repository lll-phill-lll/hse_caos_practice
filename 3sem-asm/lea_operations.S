    .global main
main:
    mov     $5, %ecx
    mov     $6, %edx

    // lea offset(base, index, mult), reg -> offset + base + index * mult -> reg
    // lea doesn't store intermediate results

    lea     2(%edx), %eax
    call    writei32

    lea     -3(%edx), %eax
    call    writei32

    lea     (%ecx, %edx), %eax
    call    writei32

    lea     4(%ecx, %edx), %eax
    call    writei32

    lea     4(, %edx), %eax
    call    writei32

    lea     4(%ecx, %edx, 2), %eax
    call    writei32

    // only 1, 2, 4, 8
    // lea     (, %edx, 3), %eax
    // call    writei32

    lea     (%edx, %edx, 2), %eax
    call    writei32

    lea     12(%edx, %edx, 2), %eax
    call    writei32

    lea     (%edx, %edx, 4), %eax
    call    writei32

    call    finish
