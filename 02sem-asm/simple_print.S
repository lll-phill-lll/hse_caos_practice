// ** Условие **
// написать функцию на ассемблере, которая будет печатать "4 5", используя printf
    .global print_4_5

print_4_5:
    push    %ebp
    mov     %esp, %ebp

    // printf("%d %d\n", 4, 5);
    // кладем аргументы с конца, потому что printf будет читать их сверху вниз на стеке
    // поэтому нужно, чтобы наверху был первый аргумент и тд
    push    $5
    push    $4

    push    $printf_format   // обычная фоорматная строка из C
    call    printf

    mov     %ebp, %esp
    pop     %ebp

    ret

    .data

printf_format:
    .string "%d %d\n"		// format string for printf
