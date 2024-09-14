    .global main
main:
    // readi32 считывает одно читсло в регистр %eax
    call    readi32
    // writei32 печатает одно число из регистра %eax
    call    writei32
    // обязательно вызываем 
    call    finish
