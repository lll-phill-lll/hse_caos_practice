    #include <sys/syscall.h>
    // strace
    // pipes

    // 0 stdin
    // 1 stdout
    // 2 stderr
    .global main
main:
   .equ     STDOUT_FILENO, 1
   .equ     STDERR_FILENO, 2
   .equ     SUCCESS, 0

   mov      $SYS_write, %eax
   mov      $STDOUT_FILENO, %ebx
   mov      $hello_out, %ecx
   mov      $hello_out_end-hello_out, %edx
   int      $0x80

   mov      $SYS_write, %eax
   mov      $STDERR_FILENO, %ebx
   mov      $hello_err, %ecx
   mov      $hello_err_end-hello_err, %edx
   int      $0x80

   mov      $SYS_exit, %eax
   mov      $SUCCESS, %ebx
   int      $0x80

hello_out:
    .asciz  "hello from stdout\n"
hello_out_end:

hello_err:
    .asciz  "hello from stderr\n"
hello_err_end:
