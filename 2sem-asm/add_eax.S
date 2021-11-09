//
//      Содержимое стека  Адреса в памяти
//
//      .                .
//      .                .
//      .                .
//      +----------------+ 0x0000F040
//      |                |
//      +----------------+ 0x0000F044 <-- вершина стека (на неё указывает %esp)
//      |     данные     |
//      +----------------+ 0x0000F048
//      |     данные     |
//      +----------------+ 0x0000F04C
//      .                .
//      .                .
//      .                .
//      +----------------+ 0x0000FFF8
//      |     данные     |
//      +----------------+ 0x0000FFFC
//      |     данные     |
//      +----------------+ 0x00010000 <-- дно стека

add_eax:
    push %ebp // save old value
    mov %esp, %ebp

    sub $8, %esp    // [    A   B   oldebp   return   xxxxx]
                    //      ^esp    ^ebp
    mov %eax, %edx
    call readi32
    mov %eax, -4(%ebp)
    call readi32
    mov %eax, -8(%ebp)

    mov %edx, %eax
    add -8(%ebp), %eax
    add -4(%ebp), %eax

    mov %ebp, %esp     // [    A   B   oldebp   return   xxxxx]
                       //              ^esp,epb
    pop %ebp           // [    A   B   oldebp   return   xxxxx]
                       //                       ^esp
    ret



    .global main
main:
    call readi32
    call add_eax
    call writei32
    call finish
