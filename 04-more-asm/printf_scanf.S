// Считать два числа и вывести их сумму и разность
// Использовать scanf + printf
    
    .global main
main:
    push    %ebp
    mov     %esp, %ebp

    // В scanf надо передать 2 адреса под переменные, которые надо считать
    // выделим 8 байт на стеке
    sub     $8, %esp
    // адрес первых 4 байт пололжим сверху на стек (3-й аргумент scanf)
    lea     -4(%ebp), %eax
    push    %eax
    // адрес следующих 4 байт положим тоже на стек (2-й аргумент scanf)
    lea     -8(%ebp), %eax
    push    %eax

    // scanf("%d %d", &A, &B)
    // положим форматную строку scanf (первый аргумент)
    push    $scanf_format
    call    scanf
    // Так как мы просили считать 2 числа, то признаком успешного завершения scanf
    // будет 2 в качестве возвращаемого значения scanf
    cmp     $2, %eax
    jne     fin

    // -4(%ebp) - B
    // -8(%ebp) - A
    // Так как вы в scanf передали адреса, куда сложить считанные инты, то 
    // и считает он их в выделенные 8 байт
    mov     -4(%ebp), %eax
    add     -8(%ebp), %eax

    mov     -8(%ebp), %edx
    sub     -4(%ebp), %edx


    // %eax - sum
    // %edx - diff
    // printf("%d %d\n", sum, diff)
    // 3-й аргумент
    push    %edx
    // 2-й аргумент
    push    %eax
    // 1-й аргумент
    push    $printf_format

    call    printf


fin:
    mov     %ebp, %esp
    pop     %ebp
    ret

    .data

printf_format:
    .string "sum: %d, diff: %d\n"		// format string for printf

scanf_format:
    .string "%d %d"
