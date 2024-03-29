// ** Условие **
// Написать функцию, которая считает 2 числа, положит их на стек
// затем сложит и вернет в eax сумму
//

read_and_add:
//  ------- пролог -------  (сохраняем значения регистров, которые мы не должны менять)
    push    %ebp            // сохраняем старое значение ebp
    mov     %esp, %ebp      // сохраняем значение esp в ebp, чтобы дальше отсчитывать адреса от ebp, так как esp будет двигаться
//  ------- конец пролога -------

    sub     $8, %esp        // выделим место под 2 инта - 8 байт. esp всегда на вершине стека,
                            // так как стек растет в сторону уменьшения адресов, то нужно вычитать из esp
                            // чтобы выделить память

    // Текущее состояние стека (слева верх, справа низ)
    //      |---|-------------------- наши два инта, для которых мы сделали sub 8. A B просто для наглядности
    //      |   |     |-------------- старое значение ebp, которое мы запушили
    //      |   |     |         |---- код возврата
    // [    A   B   oldebp   return   xxxxx]
    //      ^esp    ^ebp

    call    readi32
    mov     %eax, -4(%ebp)  // кладем в "B". Так как хотим положить "левее" ebp, то знак минус
                            // аналогично могли бы сделать mov %eax, 4(%esp), попали бы в ту же ячейку
                            // но это не очень удобно, потому что ebp статичный, а esp двигается (от пушей, например)
                            // поэтому лучше отсчитывать от ebp

    call    readi32
    mov     %eax, -8(%ebp)  // аналогично кладем в "A"

    xor     %eax, %eax      // зануляем eax
    add     -8(%ebp), %eax  // прибавляем наши A и B к eax
    add     -4(%ebp), %eax

//  ------- эпилог ------- (возвращаем сохраненные значения регистров обратно)
    mov     %ebp, %esp
    // Текущее состояние стека (слева верх, справа низ)
    // [    A   B   oldebp   return   xxxxx]
    //              ^esp,epb
    pop     %ebp
    // Текущее состояние стека (слева верх, справа низ)
    // [    A   B   oldebp   return   xxxxx xxxxx xxxxx]
    //                       ^esp                 ^ebp
//  -------  конец эпилога -------
    ret


    .global main
main:
    call    read_and_add
    call    writei32
    call    finish
