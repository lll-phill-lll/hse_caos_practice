    // ** Условие **
    // Использую системные вызовы нужно прочитать строку и увеличить каждую цифру на 5. Если получилось больше 9, то взять по модулю 10.
    // Вывести получившуюся строку.
    
    #include <sys/syscall.h>

    .global main
main:
    .equ    STDOUT_FILENO, 1
    .equ    STDIN_FILENO, 0
    .equ    SUCCESS, 0

    .equ    BUF_SIZE, 1024

    sub     $BUF_SIZE, %esp
    mov     %esp, %edi

    push    $BUF_SIZE
    push    %edi
    call    myread
    // сохраним реально считанное количество символов
    mov     %eax, %esi
    
    // счетчик символов
    xor     %ecx, %ecx
process:
    // В $edi лежим адрес начала нашего буфера. 
    // Прибавляя к нему счетчик будем получать следующий символ
    mov     (%edi, %ecx), %al
    // Проверяем, что это цифра. Код символа должен быть больше 0 и меньше 9.
    // --------------
    cmp     $'0', %al
    jl      read_next
    cmp     $'9', %al
    jg      read_next
    // --------------
    
    // Прибавим 5, если результат больше 9, то вычтем 10
    add     $5, %al
    cmp     $'9', %al
    jna     ok
    sub     $10, %al
ok:
    // Запишем получившийся символ в место буфера, куда показывает счетчик
    mov     %al, (%edi, %ecx)

read_next:
    inc     %ecx
    // Продолжаем операцию, пока счетчик не станет больше количества символов,
    // которое мы считали
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
