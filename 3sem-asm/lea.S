    .global main
    // main or arr is address to next instruction
main:
    mov     $1, %edx
    // save address to eax
    lea     arr(, %edx, 4), %eax    // arr + edx * 4 -> eax
    call    writei32
    // save value in address to eax
    mov     arr(, %edx, 4), %eax    // value(arr + edx * 4) -> eax
    call    writei32

    // same
    mov     $arr, %eax
    shl     $2, %edx
    add     %edx, %eax
    call    writei32

    call    finish

arr:
    .int    5
    .int    6
    // 200 int elements
    .skip   800
