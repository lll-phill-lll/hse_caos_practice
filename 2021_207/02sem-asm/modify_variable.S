// Код программы находится в области .text
// память можно выделить в области .text, но
// в таком случае нельзя будет изменить значения,
// которые там находятся.
// В облусти .data находятся данные, которые
// можно изменить.
// .text и .data могут быть в любых частях программы
// Если не указывать область, то будет счиаться .text
    .text
    .global main
main:

    // mov  x, y  - not alloved
    mov     x, %eax
    mov     %eax, y

    mov     y, %eax
    call    writei32
    call    finish

    .data
x:
    .int    42
y:
    .int    50
