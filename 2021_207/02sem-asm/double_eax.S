// ** условие **
// Считать значение в eax, увеличить его в 2 раза
// использовать подпрограмму

double_eax:
    add     %eax, %eax
    ret

    .global main
main:
    call    readi32
    call    double_eax  // В отличие от jmp call позволяет вернуться обратно из "функции" после вызова ret
                        // call кладет на стек адрес возврата и после вызова ret будет выполнен переход по этому адресу
    call    writei32
    call    finish
