// extern "C" void my_for_each(int* arr, int size, int (*modifier)(int* ));
.global my_for_each

my_for_each:

    push    %ebp
    mov     %esp, %ebp

    //      int* arr
    mov     8(%ebp), %eax
    //      int size
    mov     12(%ebp), %ecx
    //      int (*modifier)(int*)
    mov     16(%ebp), %edx

cycle:

    push    %ecx
    push    %edx

    push    %eax
    call    *%edx
//     push    $next_cmd
//     jmp     *%edx
// next_cmd:
    pop     %eax
    pop     %edx
    pop     %ecx

    add     $4, %eax


    loop    cycle


    mov     %ebp, %esp
    pop     %ebp

    ret
