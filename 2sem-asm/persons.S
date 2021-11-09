    .text
    .global main
main:
    call readi32
    mov %eax, %ebx

    mov persons(, %ebx, 8), %eax
    call writei32

    // mov $4, %edx
    // mov persons(%edx, %ebx, 8), %eax   addr(person) + ebx * 8 + edx -> eax

    mov persons+4(, %ebx, 8), %eax     // addr(person) + 4 + ebx * 8 -> eax
    call writei32


    call finish

    .data
persons:
    .int 80     // weight
    .int 180    // height
    .int 70
    .int 160
    .int 30
    .int 130

