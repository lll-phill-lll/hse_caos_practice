    #include <sys/syscall.h>
    .global main
main:
    // echo $? to see exit code
    mov $SYS_exit, %eax
    mov $3, %ebx
    int $0x80
