   // ** Условие **
   // Используя системные вызовы read, write напечатать 2 строки в stderr и stdout.
   
   #include <sys/syscall.h>
    
    // 0 stdin
    // 1 stdout
    // 2 stderr
    
    .global main
main:
   .equ     STDOUT_FILENO, 1
   .equ     STDERR_FILENO, 2
   .equ     SUCCESS, 0

   // ssize_t write(int fd, const void *buf, size_t count); 
   mov      $SYS_write, %eax
   mov      $STDOUT_FILENO, %ebx
   mov      $hello_out, %ecx
   // Чтобы получить длину строки, можно использовать знание, что метки содержат адреса,
   // поэтому разность меток - разность адресов, то есть размер области памяти между метками, то есть длина строки
   mov      $hello_out_end-hello_out, %edx
   int      $0x80

   // ssize_t write(int fd, const void *buf, size_t count); 
   mov      $SYS_write, %eax
   mov      $STDERR_FILENO, %ebx
   mov      $hello_err, %ecx
   mov      $hello_err_end-hello_err, %edx
   int      $0x80
   
   // void _exit(int status);
   mov      $SYS_exit, %eax
   mov      $SUCCESS, %ebx
   int      $0x80

hello_out:
    .ascii  "hello from stdout\n"
hello_out_end:

hello_err:
    .ascii  "hello from stderr\n"
hello_err_end:
