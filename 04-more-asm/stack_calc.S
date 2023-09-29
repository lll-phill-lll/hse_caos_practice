    .global main
main:
    call    readi32
    jc      fin
    jmp     *jmptab(, %eax, 4)

read_to_stack:
    call    readi32
    push    %eax
    jmp     main

pop_and_add:
    pop     %eax
    pop     %edx
    add     %edx, %eax
    push    %eax
    jmp     main

top_of_stack:
    mov     (%esp), %eax
    call    writei32
    jmp     main

pop_from_stack:
    pop     %eax
    jmp     main

fin:
    call    finish

jmptab:
    .int    read_to_stack, pop_and_add, top_of_stack, pop_from_stack
