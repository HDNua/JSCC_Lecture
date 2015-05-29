%include 'handy/handy.inc'

segment .data
sHelloWorld	db	'Hello, world!', 10, 0

segment .text
	global _main

_main:
	push	ebp
	mov	ebp,	esp
	
	push	sHelloWorld	; 명령어와 주석을 조합할 수 있습니다.
	call	print_string	; print_string 프로시저를 호출합니다.
	
	mov	eax,	0	; 빈 줄에도 주석을 달 수 있습니다.
				; 프로세스가 0 이외의 값을 반환하면
				; 정상적으로 종료되지 않은 것으로
				; 간주하기 때문에, 반환 값을 언제나
				; 0으로 맞춰주어야 합니다.
	
end1:	mov	esp,	ebp	; 구문의 모든 요소를 적용한 명령입니다.
end2:	pop	ebp
end3:	ret			; 프로시저를 반환합니다.
end4:				; _main의 경우 프로그램이 종료됩니다.