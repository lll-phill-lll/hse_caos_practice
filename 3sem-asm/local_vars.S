// Если для хранения локальных переменных не хватает регистров,
// можно использовать стек.

    .global count_spaces
    // int count_spaces(char *buf, size_t length)
count_spaces:
    .equ buf, 8
    .equ length, 12
    .equ count, -4  // Смещение переменной относительно ebp.

    push %ebp
    mov %esp, %ebp

    sub $4, %esp  // Выделяем место для переменной count.
    movl $0, count(%ebp)

    mov buf(%ebp), %eax
    mov $0, %ecx  // Индекс
    mov length(%ebp), %edx
loop:
    cmp %edx, %ecx
    je end
    cmpb $' ', (%eax, %ecx, 1)
    jne skip
    incl count(%ebp)
skip:
    inc %ecx
    jmp loop
end:
    mov count(%ebp), %eax  // Чтобы вернуть результат, переносим его в eax.

    // Эпилог. Восстанавливается esp, освобождается память, выделенная для локальных переменных.
    mov %ebp, %esp
    pop %ebp
    ret
