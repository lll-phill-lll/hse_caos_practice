#include <sys/syscall.h>

    .global _start
_start:
    // call with 0 to get end=start address
    mov     $SYS_brk, %eax
    mov     $0, %ebx
    int     $0x80

    // save address to heapstart
    mov     %eax, heapstart

    mov     %eax, %edx
    // segfault, no memory is mapped
    // movl    $42, (%edx)

    // calculate new address. Add 1MB
    add     $1<<20, %eax
    mov     %eax, %ebx

    // ask for more memory: from heapstart to heapstart + 1<<20
    mov     $SYS_brk, %eax
    int     $0x80

    // save new address to heapend
    mov     %eax, heapend

    // no segfault, memory is mapped and ready to use
    // movl    $42, (%edx)

    mov     $SYS_exit, %eax
    mov     $0, %ebx
    int     $0x80

// memory structure: [ program code ] [ program .data ] [ heap {size| .... } ] ... [ stack ]
my_malloc:
    push    %ebx

    mov     heapend, %ebx
    mov     8(%esp), %ecx
    add     %ecx, %ebx
    // add space to store size of allocated memory
    add     $4, %ebx

    mov     $SYS_brk, %eax
    int     $0x80

    mov     heapend, %ecx
    mov     %eax, heapend
    mov     %ecx, %eax
    // save size value [size|......]
    mov     8(%esp), %ecx
    mov     %ecx, (%eax)
    // change address to skip size value
    add     $4, %eax

    pop     %ebx
    ret


    mov $2, %eax
    mov $'0', %edx
    add %eax, %edx

    0 - 59
    1 - 60
    2 - 61


    // [heap{size|.....} {size|.....}]
    //                         ^     ^ heapend

// changes memory to { size|nextfree .................... }
my_free:
    // receives address that my_malloc returned
    mov     4(%esp), %ecx
    // access to size value
    sub     $4, %ecx
    // add new node to freelist
    mov     freelist, %edx
    mov     %edx, 4(%ecx)
    mov     %ecx, freelist
    ret



    .data
// store address of heap begin
heapstart:
    .int 0
// store address of heap end
heapend:
    .int 0
freelist:
    .int 0
