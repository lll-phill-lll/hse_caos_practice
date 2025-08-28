// Все библиотечные функции не меняют значения регистров rsp, rbp, rbx, r12, r13, r14, r15.
    .intel_syntax noprefix
    .global main
// ┌──────────────────────────────┐
// │             rax              │
// └───────────────┬──────────────┤
//                 │     eax      │
//                 └───────┬──────┤
//                         │  ax  │
//                         ├──┬───┤
//                         │ah│al │
//                         └──┴───┘

//  64   32     16       8
// rax 	eax 	ax 	    al
// rbx 	ebx 	bx 	    bl
// rcx 	ecx 	cx 	    cl
// rdx 	edx 	dx 	    dl
// rsi 	esi 	si 	    sil
// rdi 	edi 	di 	    dil
// rbp 	ebp 	bp 	    bpl
// rsp 	esp 	sp 	    spl
// r8 	r8d 	r8w 	r8b
// r9 	r9d 	r9w 	r9b
// r10 	r10d 	r10w 	r10b
// r11 	r11d 	r11w 	r11b
// r12 	r12d 	r12w 	r12b
// r13 	r13d 	r13w 	r13b
// r14 	r14d 	r14w 	r14b
// r15 	r15d 	r15w 	r15b

main:
    // Результат в eax
    call    readi32
    mov     r12d, eax

    // Результат в eax
    call    readi32
    // второе число
    mov     r13d, eax

    // add     DST, SRC   DST += SRC
    add     r12d, r13d

    mov     edi, r12d
    call    writei32

    call    finish










