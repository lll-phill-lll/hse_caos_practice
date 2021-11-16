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

    push    $hello_end-hello
    push    $hello
    call    print_hello

    push    %esi
    push    %edi
    call    print_hello


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

print_hello:
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

hello:
    .asciz  "hello, "
hello_end:
