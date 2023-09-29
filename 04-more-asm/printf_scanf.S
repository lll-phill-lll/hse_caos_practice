    .global main
main:
    push    %ebp
    mov     %esp, %ebp

    sub     $8, %esp
    lea     -4(%ebp), %eax
    push    %eax
    lea     -8(%ebp), %eax
    push    %eax

    // scanf("%d %d", &A, &B)
    push    $scanf_format
    call    scanf
    cmp     $2, %eax
    jne     fin

    // -4(%ebp) - B
    // -8(%ebp) - A
    mov     -4(%ebp), %eax
    add     -8(%ebp), %eax

    mov     -8(%ebp), %edx
    sub     -4(%ebp), %edx


    // %eax - sum
    // %edx - diff
    // printf("%d %d\n", sum, diff)
    push    %edx
    push    %eax
    push    $printf_format

    call    printf


fin:
    mov     %ebp, %esp
    pop     %ebp
    ret

    .data

printf_format:
    // формат: int<space>int<new line>
    .string "sum: %d, diff: %d\n"		// format string for printf

scanf_format:
    .string "%d %d"
