#include <sys/syscall.h>

    .global main
main:
    .equ    BUF_SIZE, 2

    .equ    STDOUT_FILENO, 1
    .equ    STDIN_FILENO, 0
    .equ    SUCCESS, 0

    sub     $BUF_SIZE, %esp

	// counter for symbol
    xor     %edi, %edi

refill_buf:
    mov 	$SYS_read, %eax
    mov 	$STDIN_FILENO, %ebx
    mov 	%esp, %ecx
    mov 	$BUF_SIZE, %edx
    int 	$0x80

    cmp 	$0, %eax
    je  	done

	// save actually read number of symbols
    mov		%eax, %ecx
    mov 	%esp, %edx

next_symbol:
	// increment address and read new symbol
    mov 	(%edx), %al
    inc 	%edx

    cmp 	$'a', %al
    jne     skip_increment

	// increase counter of 'a'
    inc 	%edi

skip_increment:
	dec		%ecx
	cmp 	$0, %ecx
	jnz	 	next_symbol

    // read again to the same bufer
    jmp     refill_buf

done:
    push    %edi
    push    $printf_format
    call    printf

    mov     $SYS_exit, %eax
    mov     $SUCCESS, %ebx
    int     $0x80


printf_format:
    .ascii  "%d\n"

