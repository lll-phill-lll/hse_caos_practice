
    .intel_syntax noprefix
    .global _start
_start:
    SYS_exit = 60 
    SYS_write = 1 

    // Новый модный x86_64 способ
    // Номер системного вызова передается в rax
    // армументы в rdi, rsi, rdx, r10, r8, r9
    // _exit(4)
    // mov     rax, SYS_exit
    // mov     rdi, 4
    // syscall

    // Старый немодный x86_32 способ
    // Номер системного вызова в eax
    // Аргументы в ebx, ecx, edx
    // mov     rax, 1
    // mov     rbx, 4
    // int     0x80

    mov     rax, SYS_write
    mov     rdi, 1
    lea     rsi, [rip + hello_world_out]
    mov     rdx, hello_world_end_out - hello_world_out
    syscall

    mov     rax, SYS_write
    mov     rdi, 2
    lea     rsi, [rip + hello_world_err]
    mov     rdx, hello_world_end_err - hello_world_err
    syscall

    mov     rax, SYS_exit
    mov     rdi, 4
    syscall

hello_world_out:
    .ascii  "Hello World STDOUT!\n"
hello_world_end_out:

hello_world_err:
    .ascii  "Hello World STDERR!\n"
hello_world_end_err:
