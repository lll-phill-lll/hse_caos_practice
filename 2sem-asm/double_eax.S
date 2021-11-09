double_eax:
    add %eax, %eax
    ret

    .global main
main:
    call readi32
    call double_eax
    call writei32
    call finish
