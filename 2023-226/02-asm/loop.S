// Задача: считать со строки ввода число и вывести все числа до него

    .global main
main:
    // считать из строки ввода число в %eax
    call    readi32
    // перекладываем считанное значение в счетчик
    mov     %eax, %ecx


print_num:
    // переложим значение счетчика в %eax, чтобы вывести
    mov     %ecx, %eax
    // выводим счетчик
    call    writei32

    // будет перепрыгивать в print_num пока в %ecx не окажется 0
    // %ecx
    loop    print_num
    // аналогично такому коду:
    // dec  %ecx
    // jnz  print_num

    call    finish
