	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"Adding: %i + %i = %i\n"
	.text
	.globl	add
	.type	add, @function
add:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	leal	(%rdx,%rax), %ecx
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	add, .-add
	.globl	subtract
	.type	subtract, @function
subtract:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	subl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	subtract, .-subtract
	.globl	multiply
	.type	multiply, @function
multiply:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	imull	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	multiply, .-multiply
	.globl	divide
	.type	divide, @function
divide:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %eax
	cltd
	idivl	-8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	divide, .-divide
	.globl	parseOperation
	.type	parseOperation, @function
parseOperation:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 8(%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	parseOperation, .-parseOperation
	.section	.rodata
	.align 8
.LC1:
	.string	"Opperation can only come after a number; exp"
	.text
	.globl	parseExpression
	.type	parseExpression, @function
parseExpression:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	jmp	.L11
.L26:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	testq	%rax, %rax
	jne	.L12
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	movl	$41, %edx
	cmpb	%dl, %al
	jne	.L12
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	movl	$40, %edx
	cmpb	%dl, %al
	jne	.L13
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	putchar@PLT
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$47, %eax
	je	.L14
	cmpl	$47, %eax
	jg	.L15
	cmpl	$45, %eax
	je	.L16
	cmpl	$45, %eax
	jg	.L15
	cmpl	$42, %eax
	je	.L17
	cmpl	$43, %eax
	jne	.L15
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	add
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L16:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	subtract
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L17:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	multiply
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L14:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	divide
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L15:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
.L13:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$47, %eax
	je	.L18
	cmpl	$47, %eax
	jg	.L19
	cmpl	$45, %eax
	je	.L20
	cmpl	$45, %eax
	jg	.L19
	cmpl	$42, %eax
	je	.L21
	cmpl	$43, %eax
	jne	.L19
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-1, %edi
	call	exit@PLT
.L20:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-1, %edi
	call	exit@PLT
.L21:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-1, %edi
	call	exit@PLT
.L18:
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$-1, %edi
	call	exit@PLT
.L19:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parseExpression
.L12:
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, -32(%rbp)
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	parseOperation
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	putchar@PLT
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$47, %eax
	je	.L22
	cmpl	$47, %eax
	jg	.L23
	cmpl	$45, %eax
	je	.L24
	cmpl	$45, %eax
	jg	.L23
	cmpl	$42, %eax
	je	.L25
	cmpl	$43, %eax
	jne	.L23
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	add
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L24:
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	subtract
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L25:
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	multiply
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L22:
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%eax, %ebx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	$10, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	strtol@PLT
	movl	%ebx, %esi
	movl	%eax, %edi
	call	divide
	movq	-48(%rbp), %rdx
	movl	%eax, (%rdx)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L23:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
.L11:
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L26
	nop
	nop
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	parseExpression, .-parseExpression
	.globl	removeWhiteSpace
	.type	removeWhiteSpace, @function
removeWhiteSpace:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	removeWhiteSpace, .-removeWhiteSpace
	.section	.rodata
.LC2:
	.string	"(1+2)"
.LC3:
	.string	"Result: %i\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$4, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	leaq	.LC2(%rip), %rax
	movq	%rax, -16(%rbp)
	movq	-8(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	parseExpression
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
