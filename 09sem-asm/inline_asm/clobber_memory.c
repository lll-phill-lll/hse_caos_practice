#include <stdio.h>
#include <unistd.h>  // STDIN_FILENO
#include <sys/syscall.h>  // SYS_*

int main() {
    char buf[] = "hello world\n";
    ssize_t res;

    asm (
        "int $0x80\n"
        : "=a"(res)
        : "a"(SYS_read), "b"(STDIN_FILENO), "c"(buf), "d"(sizeof(buf) - 1)
#ifdef CLOBBER_MEMORY
        : "memory"  // Входной параметр buf - указатель. read может модифицировать *buf, *(buf+1), ..., т.е. произвольную память.
#endif
    );
    buf[res] = 0;
    puts(buf);
}
