    .global print_4_5
print_4_5:
    push %ebp 			// push stack frame
    mov %esp, %ebp

    push $5
    push $4

    push $printf_format
    call printf

    mov %ebp, %esp
    pop %ebp

    ret

    .data

printf_format:
    .string "%d %d\n"		// format string for printf
