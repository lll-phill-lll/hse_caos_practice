    #include <sys/syscall.h>

    .global main
main:
    .equ    STDOUT_FILENO, 1
    .equ    STDIN_FILENO, 1
    .equ    SUCCESS, 0

    .equ    BUF_SIZE, 1024

    sub     $BUF_SIZE, %esp
    mov     %esp, %edi

    push    $BUF_SIZE
    push    %edi
    call    myread
    mov     %eax, %esi      // save result of syscall (input length)

    xor     %ecx, %ecx
process:
    mov     (%edi, %ecx), %al
    cmp     $'0', %al
    jl      read_next
    cmp     $'9', %al
    jg      read_next
    add     $5, %al
    cmp     $'9', %al
    jna     ok
    sub     $10, %al
ok:
    mov     %al, (%edi, %ecx)

read_next:
    inc     %ecx
    cmp     %ecx, %esi
    jnz     process


    push    %esi
    push    %edi
    call    mywrite


    mov     $SYS_exit, %eax
    mov     $SUCCESS, %ebx
    int     $0x80



myread:
    push    %ebp
    mov     %esp, %ebp
    push    %ebx

    mov     $SYS_read, %eax
    mov     $STDIN_FILENO, %ebx
    mov     8(%ebp), %ecx
    mov     12(%ebp), %edx

    int     $0x80

    pop     %ebx
    pop     %ebp
    ret

mywrite:
    push    %ebp
    mov     %esp, %ebp
    push    %ebx

    mov     $SYS_write, %eax
    mov     $STDOUT_FILENO, %ebx
    mov     8(%ebp), %ecx
    mov     12(%ebp), %edx

    int     $0x80

    pop     %ebx
    pop     %ebp
    ret
