// ** Условие **
// Написать функцию, которая считает число с помощью scanf,
// умножит его на 4 и выведет с помощью printf

    .global read_multiply_add

read_multiply_add:
    push    %ebp
    movl    %esp, %ebp

    //   int a;
    //   вторым аргументом в scanf должен быть указатель на место
    //   куда положить считанное число
    //   scanf("%d", &a);
    //
    //   a += 2;

    // Выделим место на стеке под 1 инт
    subl    $4, %esp
    // Возьмем адрес места на стеке, которое выделили
    leal    -4(%ebp), %eax
    pushl   %eax
    pushl   $scanf_format
    call    scanf

    movl    -4(%ebp), %eax
    sall    $2, %eax

    pushl   %eax
    pushl   $printf_format
    call    printf

    movl    %ebp, %esp
    popl    %ebp

    ret

scanf_format:
    .string "%d"

printf_format:
    .string "%d\n"
