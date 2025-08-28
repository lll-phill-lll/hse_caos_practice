    .intel_syntax noprefix
    .global main

    .data
ret_addr:
    .quad   0          

    .text

add_numbers:
    add     rdi, rax    
    mov     r12, [rip + ret_addr]
    jmp     r12                

main:
    mov     rdi, 5            
    mov     rax, 6           

    lea     r12, [rip + after_jmp] 
    mov     [rip + ret_addr], r12

    jmp     add_numbers       
after_jmp:

    call    writei64

    call    finish
