// extern "C" void my_scan(const char* fmt, ...);
.global my_scan

my_scan:
    // ---------------
    push    %ebp
    mov     %esp, %ebp
    // ---------------

    push    %esi
    push    %edi

    // %esi - fmt
    mov     8(%ebp), %esi
    // %edi - address of argument
    lea     12(%ebp), %edi

cycle:
    movb    (%esi), %al
    incl    %esi
    cmpb    $0, %al
    je      fin


    cmpb    $'d', %al
    je      read_int

    cmpb    $'l',%al
    je      read_long_long

    // we are here if char is not one of ['d', 'l']
    jmp     fin

read_int:
    call    readi32
    mov     (%edi), %ecx
    // ecx - address
    mov     %eax, (%ecx)
    add     $4, %edi
    jmp     cycle

read_long_long:
    // read to eax + edx
    call    readi64
    mov     (%edi), %ecx
    mov     %eax, (%ecx)
    mov     %edx, 4(%ecx)
    add     $4, %edi
    jmp     cycle


fin:
    pop     %edi
    pop     %esi
    // ---------------
    mov     %esp, %ebp
    pop     %ebp
    // ---------------

    ret
