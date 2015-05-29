%include 'handy/handy.inc'

; equ 지시어를 이용하여 상수를 정의합니다.
EQU_VALUE	equ		100

; % 지시어를 이용하여 상수 매크로를 정의합니다.
%define		MACRO_VALUE	200

; % 지시어를 이용하여 구문을 정의합니다. equ로는 할 수 없습니다.
%define		MOV_ESI_300	mov	esi,	300
; MOV_ESI_300_EQU	equ	mov	esi,	300

segment .text
	; _main 프로시저가 전역에서 접근 가능한 프로시저임을
	; global 지시어를 이용하여 어셈블러에 전달합니다.
	global _main

; _main 레이블 정의입니다.
_main:
	push	ebp
	mov	ebp,	esp
	
	; equ 지시어로 정의한 상수 사용 예제
	mov	esi,	EQU_VALUE
	call	print_int
	call	print_newline
	
	; % 지시어로 정의한 상수 매크로 사용 예제
	mov	esi,	MACRO_VALUE
	call	print_int
	call	print_newline
	
	; % 지시어로 정의한 구문 사용 예제
	MOV_ESI_300
	call	print_int
	call	print_newline
	
	mov	eax,	0
	mov	esp,	ebp
	pop	ebp
	ret