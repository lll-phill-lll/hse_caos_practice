    .global plus

plus:
    push   %ebp
    mov    %esp, %ebp

    // [    oldebp   return   a   b    xxxxx]
    //      ^esp, ebp
    mov    8(%ebp), %eax
    mov    12(%ebp), %edx
    add    %edx, %eax

    // mov %ebp, %esp
    pop    %ebp

    ret
