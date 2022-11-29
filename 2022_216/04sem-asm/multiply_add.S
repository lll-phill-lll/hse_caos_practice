// ** Условие **
// Написать функцию, которая примет аргументами a и b, вычислит
// a * 2 + b и вернуть значение

    .global multiply_add

multiply_add:
    // --------------
    // [ return   a   b    xxxxx ]
    //   ^esp

    push    %ebp
    // [ oldebp return   a   b    xxxxx ]
    //   ^esp

    movl    %esp, %ebp
    // [ oldebp return   a   b    xxxxx ]
    //   ^esp, ebp

    // ---------------

    // Сохраним еще рагистр %esi, чтобы безопасно можно было его использовать
    pushl   %esi
    // [ oldesi oldebp return   a   b    xxxxx ]
    //   ^esp   ^ebp

    // a - 8 так как надо оступить oldebp, return
    movl    8(%ebp), %esi

    // b - 12 так как отступаем oldebp, return, a
    movl    12(%ebp), %eax

    sal     $1, %esi
    // оставляем результат в %eax, так как возвращаемосе значение должно быть в eax по cdecl
    addl    %esi, %eax

    popl    %esi
    // [ oldebp return   a   b    xxxxx ]
    //   ^esp, ebp
    popl    %ebp
    // [ return   a   b    xxxxx ]
    //   ^esp

    ret



