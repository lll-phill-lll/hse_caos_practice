    .text
    .global main
main:
    push        %ebp
    mov         %esp, %ebp

    // s - 1 value
    // s - float
    movss       a, %xmm0
    addss       b, %xmm0
    // xmm0 -> a + b

    cvtsi2ss    d, %xmm1
    addss       c, %xmm1
    // xmm1 -> c + d

    divss       %xmm1, %xmm0

    sub         $8, %esp
    cvtss2sd    %xmm0, %xmm0
    movsd       %xmm0, (%esp)

    push        $printf_format

    call        printf

    mov         %ebp, %esp
    pop         %ebp

    .data
a:
    .float      1.1
b:
    .float      2.2
c:
    .float      3.3
d:
    .int        4



printf_format:
    .string "%f\n"
