    .global main
main:
    movb    $0xbad1dea, arr     // ea
    movw    $0xbad1dea, arr+4   // 1dea
    movl    $0xbad1dea, arr+8   // bad1dea

    mov     arr, %eax
    call    writei32

    mov     arr+4, %eax
    call    writei32

    mov     arr+8, %eax
    call    writei32

    call    finish

    .data
arr:
    // arr+8: 0xea, 0x1d, 0xad, 0x0b, 0x00
    //        0     1     2     3     4
    .skip   400, 0

