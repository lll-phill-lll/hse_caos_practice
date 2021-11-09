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

    add -8(%ebp), %eax
    add -4(%ebp), %eax

    call writei32

    mov %ebp, %esp     // [    A   B   oldebp   return   xxxxx]
                       //              ^esp,epb
    pop %ebp           // [    A   B   oldebp   return   xxxxx]
                       //                       ^esp
    ret



    .global main
main:
    call readi32
    call add_eax
    call finish
