// ** Условие **
// Завести массив из 3х человек с разным ростом и весом
// По считаному индесу выводить рост и вес человека под этим индексом

    .text
    .global main
main:
    call    readi32
    mov     %eax, %ebx

    mov     persons(, %ebx, 8), %eax        // addr(persons) + ebx * 8 -> eax; умножаем на 8 так как
                                            // хотим за один индекс проходить 2 инта в массиве
                                            // При каждом сдвиге на 8 получаем очередной вес, чтобы получить рост
                                            // нужно сдвинуть еще на 4
    call    writei32

    // могли бы сделать так, но можно лучше
    // mov $4, %edx
    // mov persons(%edx, %ebx, 8), %eax     // value(person + ebx * 8 + edx) -> eax

    mov     persons+4(, %ebx, 8), %eax      // value(person + 4 + ebx * 8) -> eax
    call    writei32


    call    finish

    .data
// будет доступен адрес только первого элемента, дальше нужно будет от первого элемента
// отсчитывать корректно индекс
persons:
    .int    80     // weight
    .int    180    // height
    .int    70
    .int    160
    .int    30
    .int    130

