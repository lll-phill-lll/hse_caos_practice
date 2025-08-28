// Все библиотечные функции не меняют значения регистров rsp, rbp, rbx, r12, r13, r14, r15.
    .intel_syntax noprefix
    .global main

// Two's complement
//      u   s
// 000 	0 	0
// 001 	1 	1
// 010 	2 	2
// 011 	3 	3
// 100 	4 	−4
// 101 	5 	−3
// 110 	6 	−2
// 111 	7 	−1

// jz      label   /* переход, если равно (нуль), ZF == 1 */
// jnz     label   /* переход, если не равно (не нуль), ZF == 0 */
// jc      label   /* переход, если CF == 1 */
// jnc     label   /* переход, если CF == 0 */
// jo      label   /* переход, если OF == 1 */
// jno     label   /* переход, если OF == 0 */
// jg      label   /* переход, если больше для знаковых чисел */
// jge     label   /* переход, если >= для знаковых чисел */
// jl      label   /* переход, если < для знаковых чисел */
// jle     label   /* переход, если <= для знаковых чисел */
// ja      label   /* переход, если > для беззнаковых чисел */
// jae     label   /* переход, если >= (беззнаковый) */
// jb      label   /* переход, если < (беззнакоый) */
// jbe     label   /* переход, если <= (беззнаковый) */

main:
    // Результат в rax
    call    readi64
    jc      end
    // первое число
    mov     r12, rax

    // Результат в rax
    call    readi64
    // второе число
    mov     r13, rax

    // add     DST, SRC   DST += SRC
    add     r12, r13

    mov     rdi, r12
    call    writei64

    jmp     main

end:
    call    finish










