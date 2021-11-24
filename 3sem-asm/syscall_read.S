// ** Условие **  
// Прочитать строку с stdin, и вывести hello, <строка>. Использовать системные вызовы.

    #include <sys/syscall.h>
    .global main
main:
    .equ    STDOUT_FILENO, 1
    .equ    STDIN_FILENO, 0
    .equ    SUCCESS, 0
    
    // размер буфер, куда мы будем читать нашу строку
    .equ    BUF_SIZE, 1024
    
    // выделим на стеке место под буфер
    sub     $BUF_SIZE, %esp
    mov     %esp, %edi

    //  вызовем myread, передадим через стек параметры
    push    $BUF_SIZE
    push    %edi
    call    myread
    // сохраним результат вызова нашей функции, по совместительству результат системного вызова. 
    // Размер реально считанных данных.
    mov     %eax, %esi

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
    
    // ssize_t read(int fd, const void *buf, size_t count); 
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

    // ssize_t write(int fd, const void *buf, size_t count); 
    mov     $SYS_write, %eax
    mov     $STDOUT_FILENO, %ebx
    mov     8(%ebp), %ecx
    mov     12(%ebp), %edx

    int     $0x80

    pop     %ebx
    pop     %ebp
    ret

hello:
    .ascii  "hello, "
hello_end:
