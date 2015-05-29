%include 'handy/handy.inc'

segment .text
	global _main

_main:
	push	ebp
	mov	ebp,	esp
	
	mov	esi,	10		; mov r32, imm (3)
	call	print_int		; 정수 출력; esi = 출력할 정수
	call	print_newline		; 개행 문자를 콘솔에 출력합니다.
	
	mov	eax,	20		; mov r32, imm (3)
	mov	esi,	eax		; mov r32, r32 (1)
	call	print_int		; esi의 값인 10을 출력합니다.
	call	print_newline
	
	mov	eax,	0
	mov	esp,	ebp
	pop	ebp
	ret