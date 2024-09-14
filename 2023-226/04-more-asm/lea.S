// ** Условие **
// Пусть есть функция, которая умеет получать адрес структуры по индексу (get_person_address)
// (На самом деле функция может как-то более хитро работать с памятью, но для текущего примера это не важно)
// Требуется считать индекс, по индексу получить адрес структуры person(height + weight) и вывести данные этого человека


    .text
get_person_address:
    // persons + edx + eax * 8 -> eax
    // Используем lea, чтобы получить адрес нужной ячейки массива
    // Множитель 8 так как за оодин индекс мы ходим пропускать 2 инта (weight + height)
    leal    persons(, %eax, 8), %eax
    ret

    .data
persons:
    .int    80     // weight
    .int    180    // height
    .int    70
    .int    160
    .int    30
    .int    130


    .text
    .global main
main:
    call    readi32

    call    get_person_address
    movl    %eax, %edx

    // Получаем weight
    movl    (%edx), %eax
    call    writei32

    // Получаем height
    movl    4(%edx), %eax
    call    writei32

    call    finish


