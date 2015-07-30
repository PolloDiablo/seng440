	.cpu arm10tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 1
	.eabi_attribute 18, 4
	.file	"optimized.c"
	.text
	.align	2
	.global	add_wc
	.type	add_wc, %function
add_wc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9}
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r5, #1
	mov	r0, #0
.L2:
	mov	r2, r5, asl #2
	ldr	r1, [r7, r2]
	ldr	ip, [r6, r2]
	add	r3, r0, r1
	and	r0, r3, #-2147483648
	and	r4, ip, #-2147483648
	add	r3, r3, ip
	str	r3, [r8, r2]
	add	r2, r0, #-2147483648
	and	r1, r1, r2
	and	r2, r0, r4
	orr	r1, r1, r2
	and	r3, r3, #-2147483648
	add	r3, r3, #-2147483648
	orr	r0, r0, r4
	and	r3, r3, r0
	orr	r1, r1, r3
	mov	r0, r1, lsr #31
	sub	r5, r5, #1
	cmn	r5, #1
	bne	.L2
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9}
	bx	lr
	.size	add_wc, .-add_wc
	.align	2
	.global	rightshift_wc
	.type	rightshift_wc, %function
rightshift_wc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r3, [r0, #0]
	mov	r1, r0
	ldr	ip, [r1, #4]!
	mov	r2, r3, lsr #1
	str	r2, [r0, #0]
	mov	r3, r3, asl #31
	orr	r3, r3, ip, lsr #1
	str	r3, [r1, #0]
	bx	lr
	.size	rightshift_wc, .-rightshift_wc
	.align	2
	.global	print_array
	.type	print_array, %function
print_array:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r5, r0
	ldr	r4, .L9
	mov	r0, r4
	ldr	r1, [r5, #0]
	bl	printf
	mov	r0, r4
	ldr	r1, [r5, #4]
	bl	printf
	mov	r0, #10
	bl	putchar
	ldmfd	sp!, {r4, r5, r6, pc}
.L10:
	.align	2
.L9:
	.word	.LC0
	.size	print_array, .-print_array
	.align	2
	.global	mmm
	.type	mmm, %function
mmm:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	sub	sp, sp, #40
	push	{lr}
	bl	__gnu_mcount_nc
	str	r0, [sp, #20]
	mov	r4, r1
	str	r2, [sp, #16]
	ldr	r2, .L22
	add	ip, sp, #32
	ldmia	r2, {r0, r1}
	stmia	ip, {r0, r1}
	add	r2, sp, #24
	ldmia	r4, {r0, r1}
	stmia	r2, {r0, r1}
	mov	r8, #0
	ldr	r2, [sp, #16]
	str	r2, [sp, #12]
	add	r2, sp, #32
	sub	r2, r2, #8
	str	r2, [sp, #8]
	str	r3, [sp, #4]
.L17:
	ldr	r7, [sp, #28]
	ldr	fp, [sp, #36]
	ldr	r3, [sp, #16]
	ldr	r9, [r3, #4]
	ands	sl, r7, #1
	moveq	r6, #0
	beq	.L13
	add	r4, sp, #32
	ldr	r5, [sp, #12]
	mov	r6, #0
.L14:
	ldr	r1, [r4, #4]
	ldr	r2, [r5, #4]
	add	r3, r6, r1
	and	r0, r3, #-2147483648
	and	ip, r2, #-2147483648
	add	r3, r3, r2
	str	r3, [r4, #4]
	add	r2, r0, #-2147483648
	and	r1, r1, r2
	and	r2, r0, ip
	orr	r1, r1, r2
	and	r3, r3, #-2147483648
	add	r3, r3, #-2147483648
	orr	r0, r0, ip
	and	r3, r3, r0
	orr	r1, r1, r3
	mov	r6, r1, lsr #31
	sub	r4, r4, #4
	sub	r5, r5, #4
	ldr	r2, [sp, #8]
	cmp	r4, r2
	bne	.L14
.L13:
	and	r3, r9, sl
	add	r3, fp, r3
	tst	r3, #1
	beq	.L15
	add	r4, sp, #32
	ldr	r5, [sp, #4]
	mov	r3, #0
.L16:
	ldr	r1, [r4, #4]
	ldr	r2, [r5, #4]
	add	r3, r3, r1
	and	r0, r3, #-2147483648
	and	ip, r2, #-2147483648
	add	r3, r3, r2
	str	r3, [r4, #4]
	add	r2, r0, #-2147483648
	and	r1, r1, r2
	and	r2, r0, ip
	orr	r1, r1, r2
	and	r3, r3, #-2147483648
	add	r3, r3, #-2147483648
	orr	r0, r0, ip
	and	r3, r3, r0
	orr	r1, r1, r3
	mov	r3, r1, lsr #31
	sub	r4, r4, #4
	sub	r5, r5, #4
	ldr	r2, [sp, #8]
	cmp	r4, r2
	bne	.L16
	add	r6, r6, r3
.L15:
	ldr	r1, [sp, #32]
	mov	r3, r1, asl #31
	ldr	r2, [sp, #36]
	orr	r3, r3, r2, lsr #1
	str	r3, [sp, #36]
	mov	r3, r6, asl #31
	orr	r3, r3, r1, lsr #1
	str	r3, [sp, #32]
	ldr	r3, [sp, #24]
	mov	r2, r3, lsr #1
	str	r2, [sp, #24]
	mov	r3, r3, asl #31
	orr	r3, r3, r7, lsr #1
	str	r3, [sp, #28]
	add	r8, r8, #1
	cmp	r8, #64
	bne	.L17
	add	r3, sp, #32
	ldmia	r3, {r0, r1}
	ldr	r3, [sp, #20]
	stmia	r3, {r0, r1}
	add	sp, sp, #40
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
	bx	lr
.L23:
	.align	2
.L22:
	.word	.LANCHOR0
	.size	mmm, .-mmm
	.align	2
	.global	mme
	.type	mme, %function
mme:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, sl, lr}
	sub	sp, sp, #44
	push	{lr}
	bl	__gnu_mcount_nc
	mov	sl, r0
	mov	r6, r1
	mov	r5, r2
	mov	r7, r3
	ldr	r4, .L29
	add	ip, sp, #32
	add	r2, r4, #8
	ldmia	r2, {r0, r1}
	stmia	ip, {r0, r1}
	add	r4, r4, #16
	add	r0, sp, #24
	mov	r1, ip
	mov	r2, r4
	bl	mmm
	add	r0, sp, #16
	mov	r1, r4
	mov	r2, r6
	mov	r3, r7
	bl	mmm
	mov	r3, sp
	ldmia	r5, {r0, r1}
	stmia	r3, {r0, r1}
	mov	r4, #0
	add	r6, sp, #8
	add	r5, sp, #16
	add	r8, sp, #24
.L26:
	mov	r0, r6
	mov	r1, r5
	mov	r2, r5
	mov	r3, r7
	bl	mmm
	ldr	r3, [sp, #4]
	tst	r3, #1
	beq	.L25
	mov	r0, r8
	mov	r1, r8
	mov	r2, r5
	mov	r3, r7
	bl	mmm
.L25:
	ldmia	r6, {r0, r1}
	stmia	r5, {r0, r1}
	ldr	r3, [sp, #0]
	mov	r2, r3, lsr #1
	str	r2, [sp, #0]
	mov	r3, r3, asl #31
	ldr	r2, [sp, #4]
	orr	r3, r3, r2, lsr #1
	str	r3, [sp, #4]
	add	r4, r4, #1
	cmp	r4, #64
	bne	.L26
	mov	r0, sl
	add	r1, sp, #32
	add	r2, sp, #24
	mov	r3, r7
	bl	mmm
	add	sp, sp, #44
	ldmfd	sp!, {r4, r5, r6, r7, r8, sl, pc}
.L30:
	.align	2
.L29:
	.word	.LANCHOR0
	.size	mme, .-mme
	.align	2
	.global	decrypt
	.type	decrypt, %function
decrypt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	push	{lr}
	bl	__gnu_mcount_nc
	bl	mme
	ldmfd	sp!, {r4, pc}
	.size	decrypt, .-decrypt
	.align	2
	.global	encrypt
	.type	encrypt, %function
encrypt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	push	{lr}
	bl	__gnu_mcount_nc
	bl	mme
	ldmfd	sp!, {r4, pc}
	.size	encrypt, .-encrypt
	.align	2
	.global	full_test
	.type	full_test, %function
full_test:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #24
	push	{lr}
	bl	__gnu_mcount_nc
	add	r3, sp, #16
	ldr	r2, .L39
	ldmia	r2, {r0, r1}
	stmia	r3, {r0, r1}
	mov	r4, #0
	add	r6, sp, #8
	add	r9, sp, #16
	ldr	r3, .L39+4
	add	sl, r3, #32
	add	r5, r3, #40
	mov	r8, sp
	add	r7, r3, #48
.L36:
	mov	r0, r6
	mov	r1, r9
	mov	r2, sl
	mov	r3, r5
	bl	encrypt
	mov	r0, sp
	mov	r1, r6
	mov	r2, r7
	mov	r3, r5
	bl	decrypt
	add	r4, r4, #1
	cmp	r4, #1000
	bne	.L36
	add	r0, sp, #8
	bl	print_array
	mov	r0, sp
	bl	print_array
	add	sp, sp, #24
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
.L40:
	.align	2
.L39:
	.word	.LANCHOR0+24
	.word	.LANCHOR0
	.size	full_test, .-full_test
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	push	{lr}
	bl	__gnu_mcount_nc
	bl	full_test
	mov	r0, #0
	bl	exit
	.size	main, .-main
	.align	2
	.global	mont_test
	.type	mont_test, %function
mont_test:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, lr}
	sub	sp, sp, #32
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	ip, .L45
	add	lr, sp, #16
	add	r3, ip, #56
	ldmia	r3, {r0, r1}
	stmia	lr, {r0, r1}
	add	r2, sp, #8
	add	r3, ip, #64
	ldmia	r3, {r0, r1}
	stmia	r2, {r0, r1}
	mov	r3, sp
	add	ip, ip, #72
	ldmia	ip, {r0, r1}
	stmia	r3, {r0, r1}
	add	r4, sp, #24
	mov	r0, r4
	mov	r1, lr
	bl	mmm
	mov	r0, r4
	bl	print_array
	add	sp, sp, #32
	ldmfd	sp!, {r4, pc}
.L46:
	.align	2
.L45:
	.word	.LANCHOR0
	.size	mont_test, .-mont_test
	.global	DEBUG_LINES
	.global	P
	.global	Q
	.global	M
	.global	E
	.global	D
	.global	Nr
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	C.20.2745, %object
	.size	C.20.2745, 8
C.20.2745:
	.space	8
	.type	C.19.2725, %object
	.size	C.19.2725, 8
C.19.2725:
	.word	0
	.word	1
	.type	Nr, %object
	.size	Nr, 8
Nr:
	.word	197716994
	.word	-272997061
	.type	C.18.2697, %object
	.size	C.18.2697, 8
C.18.2697:
	.word	0
	.word	18505
	.type	E, %object
	.size	E, 8
E:
	.word	0
	.word	149
	.type	M, %object
	.size	M, 8
M:
	.word	994211717
	.word	1848082007
	.type	D, %object
	.size	D, 8
D:
	.word	313610406
	.word	-1766748923
	.type	C.15.2685, %object
	.size	C.15.2685, 8
C.15.2685:
	.word	0
	.word	17
	.type	C.16.2686, %object
	.size	C.16.2686, 8
C.16.2686:
	.word	0
	.word	22
	.type	C.17.2687, %object
	.size	C.17.2687, 8
C.17.2687:
	.word	0
	.word	23
	.type	P, %object
	.size	P, 8
P:
	.word	2
	.word	-667965587
	.type	Q, %object
	.size	Q, 8
Q:
	.word	0
	.word	349523539
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%08x \000"
	.bss
	.align	2
	.type	DEBUG_LINES, %object
	.size	DEBUG_LINES, 4
DEBUG_LINES:
	.space	4
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
