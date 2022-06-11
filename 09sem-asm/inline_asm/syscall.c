#include <stdio.h>
#include <stdint.h>
#include <sys/syscall.h>  // SYS_*

int main() {
    uintptr_t heapend;
	asm (
        "int $0x80\n"
		: "=a"(heapend)  // Значение eax после выполнения вставки запишется в heapend. Если регистр указан в outputs, его не нужно указывать в clobbers.
		: "a"(SYS_brk), "b"(NULL)  // Перед выполнением вставки eax = SYS_brk, ebx = NULL.
    );
    printf("%p\n", (void*) heapend);
}
