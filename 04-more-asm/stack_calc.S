// Стековый колькулятор
// Команды:
// 0 n - положить n на стек
// 1 - сложить 2 числа на стеке
// 2 - вывести верхнее число со стека
// 3 - удалить верхнее число со стека

    .global main
main:
    call    readi32
    jc      fin
    // Прыгаем на метку, индекс которой нам ввели
    jmp     *jmptab(, %eax, 4)

read_to_stack:
    call    readi32
    push    %eax
    jmp     main

pop_and_add:
    pop     %eax
    pop     %edx
    add     %edx, %eax
    push    %eax
    jmp     main

top_of_stack:
    mov     (%esp), %eax
    call    writei32
    jmp     main

pop_from_stack:
    pop     %eax
    jmp     main

fin:
    call    finish

jmptab:
    // Сохраним адреса меток в таблицу переходов
    .int    read_to_stack, pop_and_add, top_of_stack, pop_from_stack
