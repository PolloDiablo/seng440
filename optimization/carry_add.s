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
	stmfd	sp!, {r4, r5, r6, r7, r8, sl}
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r8, r0
	mov	r7, r1
	mov	r6, r2
	mov	r4, #7
	mov	r2, #0
.L2:
	ldrb	r1, [r7, r4]	@ zero_extendqisi2
	ldrb	r0, [r6, r4]	@ zero_extendqisi2
	add	r2, r2, r1
	lsr	r3, r2, #7
	and	r3, r3, #1
	add	r2, r2, r0
	lsr	r1, r2, #7
	orr	r1, r3, r1
	strb	r2, [r8, r4]
	mov	r1, r2
	sub	r4, r4, #1
	cmn	r4, #1
	bne	.L2
	mov	r0, r2
	ldmfd	sp!, {r4, r5, r6, r7, r8, sl}
	bx	lr
	.size	add_wc, .-add_wc
	.align	2
	.global	rightshift_wc
	.type	rightshift_wc, %function
rightshift_wc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	stmfd	sp!, {r4, r5}
	push	{lr}
	bl	__gnu_mcount_nc
	ldrb	r3, [r0, #0]	@ zero_extendqisi2
	mov	r1, r0
	ldrb	ip, [r1, #1]!	@ zero_extendqisi2
	mov	r2, r3, lsr #1
	strb	r2, [r0, #0]
	mov	r3, r3, asl #7
	orr	r3, r3, ip, lsr #1
	strb	r3, [r1, #0]
	mov	r2, r0
	ldrb	r3, [r2, #2]!	@ zero_extendqisi2
	mov	r1, r0
	ldrb	r4, [r1, #3]!	@ zero_extendqisi2
	mov	ip, ip, asl #7
	orr	ip, ip, r3, lsr #1
	strb	ip, [r2, #0]
	mov	r3, r3, asl #7
	orr	r3, r3, r4, lsr #1
	strb	r3, [r1, #0]
	mov	r2, r0
	ldrb	r3, [r2, #4]!	@ zero_extendqisi2
	mov	r1, r0
	ldrb	ip, [r1, #5]!	@ zero_extendqisi2
	mov	r4, r4, asl #7
	orr	r4, r4, r3, lsr #1
	strb	r4, [r2, #0]
	mov	r3, r3, asl #7
	orr	r3, r3, ip, lsr #1
	strb	r3, [r1, #0]
	mov	r2, r0
	ldrb	r3, [r2, #6]!	@ zero_extendqisi2
	ldrb	r1, [r0, #7]!	@ zero_extendqisi2
	mov	ip, ip, asl #7
	orr	ip, ip, r3, lsr #1
	strb	ip, [r2, #0]
	mov	r3, r3, asl #7
	orr	r3, r3, r1, lsr #1
	strb	r3, [r0, #0]
	ldmfd	sp!, {r4, r5}
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
	mov	r4, #0
	ldr	r6, .L11
.L8:
	mov	r0, r6
	ldrb	r1, [r5, r4]	@ zero_extendqisi2
	bl	printf
	add	r4, r4, #1
	cmp	r4, #8
	bne	.L8
	mov	r0, #10
	bl	putchar
	ldmfd	sp!, {r4, r5, r6, pc}
.L12:
	.align	2
.L11:
	.word	.LC0
	.size	print_array, .-print_array
	.align	2
	.global	mmm
	.type	mmm, %function
mmm:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #28
	push	{lr}
	bl	__gnu_mcount_nc
	str	r0, [sp, #4]
	mov	r5, r1
	mov	fp, r2
	str	r3, [sp, #0]
	mov	r4, #8
	add	r0, sp, #16
	ldr	r1, .L24
	mov	r2, r4
	bl	memcpy
	add	r0, sp, r4
	mov	r1, r5
	mov	r2, r4
	bl	memcpy
	mov	r9, #0
	add	r6, sp, #16
	mvn	r5, #127
.L19:
	ldrb	r3, [sp, #15]	@ zero_extendqisi2
	ldrb	sl, [sp, #23]	@ zero_extendqisi2
	ldrb	r8, [fp, #7]	@ zero_extendqisi2
	ands	r7, r3, #1
	moveq	r4, #0
	beq	.L15
	mov	lr, #7
	mov	r4, #0
.L16:
	ldrb	r1, [r6, lr]	@ zero_extendqisi2
	ldrb	r0, [fp, lr]	@ zero_extendqisi2
	add	r2, r4, r1
	and	r3, r2, #255
	and	r2, r2, #128
	and	ip, r0, #128
	add	r3, r3, r0
	strb	r3, [r6, lr]
	eor	r0, r2, r5
	and	r1, r1, r0
	and	r0, r2, ip
	and	r3, r3, #128
	eor	r3, r3, r5
	orr	r2, r2, ip
	orr	r1, r1, r0
	and	r3, r3, r2
	orr	r1, r1, r3
	and	r1, r1, #255
	mov	r1, r1, lsr #7
	and	r4, r1, #255
	sub	lr, lr, #1
	cmn	lr, #1
	bne	.L16
.L15:
	and	r3, r8, r7
	add	r3, sl, r3
	tst	r3, #1
	beq	.L17
	mov	lr, #7
	mov	r2, #0
.L18:
	ldrb	r1, [r6, lr]	@ zero_extendqisi2
	ldr	r3, [sp, #0]
	ldrb	r0, [r3, lr]	@ zero_extendqisi2
	add	r2, r2, r1
	and	r3, r2, #255
	and	r2, r2, #128
	and	ip, r0, #128
	add	r3, r3, r0
	strb	r3, [r6, lr]
	eor	r0, r2, r5
	and	r1, r1, r0
	and	r0, r2, ip
	and	r3, r3, #128
	eor	r3, r3, r5
	orr	r2, r2, ip
	orr	r1, r1, r0
	and	r3, r3, r2
	orr	r1, r1, r3
	and	r1, r1, #255
	mov	r1, r1, lsr #7
	and	r2, r1, #255
	sub	lr, lr, #1
	cmn	lr, #1
	bne	.L18
	add	r3, r2, r4
	and	r4, r3, #255
.L17:
	ldrb	r3, [sp, #16]	@ zero_extendqisi2
	ldrb	r1, [sp, #17]	@ zero_extendqisi2
	mov	r2, r3, lsr #1
	strb	r2, [sp, #16]
	mov	r3, r3, asl #7
	orr	r3, r3, r1, lsr #1
	strb	r3, [sp, #17]
	ldrb	r3, [sp, #18]	@ zero_extendqisi2
	ldrb	r2, [sp, #19]	@ zero_extendqisi2
	mov	r1, r1, asl #7
	orr	r1, r1, r3, lsr #1
	strb	r1, [sp, #18]
	mov	r3, r3, asl #7
	orr	r3, r3, r2, lsr #1
	strb	r3, [sp, #19]
	ldrb	r3, [sp, #20]	@ zero_extendqisi2
	ldrb	r1, [sp, #21]	@ zero_extendqisi2
	mov	r2, r2, asl #7
	orr	r2, r2, r3, lsr #1
	strb	r2, [sp, #20]
	mov	r3, r3, asl #7
	orr	r3, r3, r1, lsr #1
	strb	r3, [sp, #21]
	ldrb	r3, [sp, #22]	@ zero_extendqisi2
	ldrb	r2, [sp, #23]	@ zero_extendqisi2
	mov	r1, r1, asl #7
	orr	r1, r1, r3, lsr #1
	strb	r1, [sp, #22]
	mov	r3, r3, asl #7
	orr	r3, r3, r2, lsr #1
	strb	r3, [sp, #23]
	ldrb	r3, [sp, #16]	@ zero_extendqisi2
	orr	r3, r3, r4, asl #7
	strb	r3, [sp, #16]
	ldrb	r3, [sp, #8]	@ zero_extendqisi2
	ldrb	r1, [sp, #9]	@ zero_extendqisi2
	mov	r2, r3, lsr #1
	strb	r2, [sp, #8]
	mov	r3, r3, asl #7
	orr	r3, r3, r1, lsr #1
	strb	r3, [sp, #9]
	ldrb	r3, [sp, #10]	@ zero_extendqisi2
	ldrb	r2, [sp, #11]	@ zero_extendqisi2
	mov	r1, r1, asl #7
	orr	r1, r1, r3, lsr #1
	strb	r1, [sp, #10]
	mov	r3, r3, asl #7
	orr	r3, r3, r2, lsr #1
	strb	r3, [sp, #11]
	ldrb	r3, [sp, #12]	@ zero_extendqisi2
	ldrb	r1, [sp, #13]	@ zero_extendqisi2
	mov	r2, r2, asl #7
	orr	r2, r2, r3, lsr #1
	strb	r2, [sp, #12]
	mov	r3, r3, asl #7
	orr	r3, r3, r1, lsr #1
	strb	r3, [sp, #13]
	ldrb	r3, [sp, #14]	@ zero_extendqisi2
	ldrb	r2, [sp, #15]	@ zero_extendqisi2
	mov	r1, r1, asl #7
	orr	r1, r1, r3, lsr #1
	strb	r1, [sp, #14]
	mov	r3, r3, asl #7
	orr	r3, r3, r2, lsr #1
	strb	r3, [sp, #15]
	add	r9, r9, #1
	cmp	r9, #64
	bne	.L19
	ldr	r0, [sp, #4]
	add	r1, sp, #16
	mov	r2, #8
	bl	memcpy
	add	sp, sp, #28
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
.L25:
	.align	2
.L24:
	.word	.LANCHOR0
	.size	mmm, .-mmm
	.align	2
	.global	mme
	.type	mme, %function
mme:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, lr}
	sub	sp, sp, #40
	push	{lr}
	bl	__gnu_mcount_nc
	mov	r9, r0
	mov	r7, r1
	mov	r8, r2
	mov	sl, r3
	ldr	r4, .L31
	add	r5, sp, #32
	mov	r6, #8
	mov	r0, r5
	add	r1, r4, r6
	mov	r2, r6
	bl	memcpy
	add	r4, r4, #16
	add	r0, sp, #24
	mov	r1, r5
	mov	r2, r4
	mov	r3, sl
	bl	mmm
	add	r0, sp, #16
	mov	r1, r4
	mov	r2, r7
	mov	r3, sl
	bl	mmm
	mov	r0, sp
	mov	r1, r8
	mov	r2, r6
	bl	memcpy
	mov	r4, #0
	add	r6, sp, r6
	add	r5, sp, #16
	add	r7, sp, #24
.L28:
	mov	r0, r6
	mov	r1, r5
	mov	r2, r5
	mov	r3, sl
	bl	mmm
	ldrb	r3, [sp, #7]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L27
	mov	r0, r7
	mov	r1, r7
	mov	r2, r5
	mov	r3, sl
	bl	mmm
.L27:
	ldmia	r6, {r0, r1}
	stmia	r5, {r0, r1}
	ldrb	r3, [sp, #0]	@ zero_extendqisi2
	ldrb	r1, [sp, #1]	@ zero_extendqisi2
	mov	r2, r3, lsr #1
	strb	r2, [sp, #0]
	mov	r3, r3, asl #7
	orr	r3, r3, r1, lsr #1
	strb	r3, [sp, #1]
	ldrb	r3, [sp, #2]	@ zero_extendqisi2
	ldrb	r2, [sp, #3]	@ zero_extendqisi2
	mov	r1, r1, asl #7
	orr	r1, r1, r3, lsr #1
	strb	r1, [sp, #2]
	mov	r3, r3, asl #7
	orr	r3, r3, r2, lsr #1
	strb	r3, [sp, #3]
	ldrb	r3, [sp, #4]	@ zero_extendqisi2
	ldrb	r1, [sp, #5]	@ zero_extendqisi2
	mov	r2, r2, asl #7
	orr	r2, r2, r3, lsr #1
	strb	r2, [sp, #4]
	mov	r3, r3, asl #7
	orr	r3, r3, r1, lsr #1
	strb	r3, [sp, #5]
	ldrb	r3, [sp, #6]	@ zero_extendqisi2
	ldrb	r2, [sp, #7]	@ zero_extendqisi2
	mov	r1, r1, asl #7
	orr	r1, r1, r3, lsr #1
	strb	r1, [sp, #6]
	mov	r3, r3, asl #7
	orr	r3, r3, r2, lsr #1
	strb	r3, [sp, #7]
	add	r4, r4, #1
	cmp	r4, #64
	bne	.L28
	mov	r0, r9
	add	r1, sp, #32
	add	r2, sp, #24
	mov	r3, sl
	bl	mmm
	add	sp, sp, #40
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, pc}
.L32:
	.align	2
.L31:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, lr}
	sub	sp, sp, #28
	push	{lr}
	bl	__gnu_mcount_nc
	add	r0, sp, #16
	ldr	r1, .L41
	mov	r2, #8
	bl	memcpy
	mov	r4, #0
	add	r6, sp, #8
	add	r9, sp, #16
	ldr	fp, .L41+4
	add	sl, fp, #32
	add	r5, fp, #40
	mov	r8, sp
	add	r7, fp, #48
.L38:
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
	bne	.L38
	add	r0, sp, #8
	bl	print_array
	mov	r0, sp
	bl	print_array
	add	sp, sp, #28
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, sl, fp, pc}
.L42:
	.align	2
.L41:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, lr}
	sub	sp, sp, #32
	push	{lr}
	bl	__gnu_mcount_nc
	ldr	r5, .L47
	add	r8, sp, #16
	mov	r4, #8
	mov	r0, r8
	add	r1, r5, #56
	mov	r2, r4
	bl	memcpy
	add	r7, sp, r4
	mov	r0, r7
	add	r1, r5, #64
	mov	r2, r4
	bl	memcpy
	mov	r6, sp
	mov	r0, sp
	add	r1, r5, #72
	mov	r2, r4
	bl	memcpy
	add	r4, sp, #24
	mov	r0, r4
	mov	r1, r8
	mov	r2, r7
	mov	r3, sp
	bl	mmm
	mov	r0, r4
	bl	print_array
	add	sp, sp, #32
	ldmfd	sp!, {r4, r5, r6, r7, r8, pc}
.L48:
	.align	2
.L47:
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
.LANCHOR0 = . + 0
	.type	C.20.2745, %object
	.size	C.20.2745, 8
C.20.2745:
	.space	8
	.type	C.19.2725, %object
	.size	C.19.2725, 8
C.19.2725:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.type	Nr, %object
	.size	Nr, 8
Nr:
	.byte	11
	.byte	-56
	.byte	-20
	.byte	2
	.byte	-17
	.byte	-70
	.byte	101
	.byte	59
	.type	C.18.2697, %object
	.size	C.18.2697, 8
C.18.2697:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	72
	.byte	73
	.type	E, %object
	.size	E, 8
E:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-107
	.type	M, %object
	.size	M, 8
M:
	.byte	59
	.byte	66
	.byte	119
	.byte	-123
	.byte	110
	.byte	39
	.byte	126
	.byte	87
	.type	D, %object
	.size	D, 8
D:
	.byte	18
	.byte	-79
	.byte	80
	.byte	-90
	.byte	-106
	.byte	-79
	.byte	-115
	.byte	5
	.type	C.15.2685, %object
	.size	C.15.2685, 8
C.15.2685:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	17
	.type	C.16.2686, %object
	.size	C.16.2686, 8
C.16.2686:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	22
	.type	C.17.2687, %object
	.size	C.17.2687, 8
C.17.2687:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	23
	.type	P, %object
	.size	P, 8
P:
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	-40
	.byte	47
	.byte	-89
	.byte	109
	.type	Q, %object
	.size	Q, 8
Q:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	20
	.byte	-43
	.byte	78
	.byte	83
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%02x \000"
	.bss
	.align	2
	.type	DEBUG_LINES, %object
	.size	DEBUG_LINES, 4
DEBUG_LINES:
	.space	4
	.ident	"GCC: (Sourcery G++ Lite 2008q3-72) 4.3.2"
	.section	.note.GNU-stack,"",%progbits
