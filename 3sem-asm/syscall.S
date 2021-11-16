    #include <sys/syscall.h>
    .global main
main:
    // echo $? to see exit code
    // mov $1, %eax
    // .equ SYS_exit 1
    mov $SYS_exit, %eax
    mov $4, %ebx

    int $0x80



    // exit(3)
