	.file	"bank_add_threads.c"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	print_account
	.type	print_account, @function
print_account:
.LFB0:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	DWORD PTR -20[rbp], edi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	eax, DWORD PTR -20[rbp]
	mov	DWORD PTR -12[rbp], eax
	mov	eax, DWORD PTR -12[rbp]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	nop
	mov	rax, QWORD PTR -8[rbp]
	sub	rax, QWORD PTR fs:40
	je	.L2
	call	__stack_chk_fail@PLT
.L2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	print_account, .-print_account
	.globl	add_money
	.type	add_money, @function
add_money:
.LFB1:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR -24[rbp], rdi
	mov	DWORD PTR -28[rbp], esi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	eax, DWORD PTR -28[rbp]
	mov	DWORD PTR -16[rbp], eax
	mov	eax, DWORD PTR -16[rbp]
	mov	ecx, eax
	mov	rdx, QWORD PTR -24[rbp]
	mov	eax, ecx
	lock xadd	DWORD PTR [rdx], eax
	add	eax, ecx
	mov	DWORD PTR -12[rbp], eax
	nop
	mov	rax, QWORD PTR -8[rbp]
	sub	rax, QWORD PTR fs:40
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	add_money, .-add_money
	.globl	child_action
	.type	child_action, @function
child_action:
.LFB2:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR -24[rbp], rdi
	mov	rax, QWORD PTR -24[rbp]
	mov	QWORD PTR -8[rbp], rax
	mov	DWORD PTR -12[rbp], 0
	jmp	.L6
.L7:
	mov	rax, QWORD PTR -8[rbp]
	mov	esi, 1
	mov	rdi, rax
	call	add_money
	add	DWORD PTR -12[rbp], 1
.L6:
	cmp	DWORD PTR -12[rbp], 100000
	jne	.L7
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	child_action, .-child_action
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	DWORD PTR -44[rbp], 0
	mov	eax, DWORD PTR -44[rbp]
	mov	edi, eax
	call	print_account
	mov	DWORD PTR -40[rbp], 0
	jmp	.L10
.L11:
	lea	rax, -32[rbp]
	mov	edx, DWORD PTR -40[rbp]
	movsx	rdx, edx
	sal	rdx, 3
	lea	rdi, [rax+rdx]
	lea	rax, -44[rbp]
	mov	rcx, rax
	lea	rax, child_action[rip]
	mov	rdx, rax
	mov	esi, 0
	call	pthread_create@PLT
	add	DWORD PTR -40[rbp], 1
.L10:
	cmp	DWORD PTR -40[rbp], 2
	jne	.L11
	mov	DWORD PTR -36[rbp], 0
	jmp	.L12
.L13:
	mov	eax, DWORD PTR -36[rbp]
	cdqe
	mov	rax, QWORD PTR -32[rbp+rax*8]
	mov	esi, 0
	mov	rdi, rax
	call	pthread_join@PLT
	add	DWORD PTR -36[rbp], 1
.L12:
	cmp	DWORD PTR -36[rbp], 2
	jne	.L13
	mov	eax, DWORD PTR -44[rbp]
	mov	edi, eax
	call	print_account
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L15
	call	__stack_chk_fail@PLT
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
