// ** Условие **
// Написать функцию, которая считает 2 числа и вызовет функцию
// multiply_add и напечатает результат вызова

    .global main
main:
    // считываем a
    call    readi32
    movl    %eax, %edx
    // считываем b
    call    readi32

    // кладем сначала b (потому что класть нужно в обратноом порядке)
    pushl   %eax
    // кладем a
    pushl   %edx
    call    multiply_add

    // Результат вызова multiply_add будет лежать в %eax, поэтому можем сразв вывести
    call    writei32

    call    finish

