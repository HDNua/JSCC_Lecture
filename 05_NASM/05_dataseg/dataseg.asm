%include 'handy/handy.inc'

; 데이터 세그먼트의 시작을 알리는 segment .data 지시어입니다.
segment .data
L1	db	0	; L1의 바이트 값을 0으로 설정
L2	dw	1000	; L2의 워드 값을 1000으로 설정
L3	db	110101b	; L3의 바이트 값을 110101_2로 설정
L4	db	17o	; L4의 바이트 값을 17_8로 설정
L5	dd	1A92h	; L5의 더블워드 값을 1A92_16으로 설정
L6	resb	1	; L6을 1바이트 메모리로 정의하고 초기화하지 않음
L7	db	"A"	; L7의 바이트 값을 문자 A의 ASCII 값으로 설정
L8	db	0, 1, 2, 3		; 4바이트를 정의
L9	db	"w", "o", "r", "d", 0	; C 문자열 "word"를 정의
L10	db	'word', 0		; L10과 같음
L11	times	100	db	0	; 100개의 db 0을 나열한 것과 같다

; 코드 세그먼트의 시작을 알리는 segment .text 지시어입니다.
segment .text
	global _main
_main:
	push	ebp
	mov	ebp,	esp
	
	mov	al,	[L1]	; al에 L1에 위치한 데이터를 대입한다
	mov	eax,	L1	; eax = L1에 위치한 바이트의 주소
	mov	[L1],	ah	; L1에 위치한 바이트에 ah를 대입한다
	mov	eax,	[L6]	; L6에 위치한 더블워드를 eax에 대입한다
	add	eax,	[L6]	; eax = eax + L6에 위치한 더블워드
	add	[L6],	eax	; L6에 위치한 더블워드 += eax
	mov	al,	[L6]	; L6에 위치한 더블워드의 하위 비트를
				; al에 대입한다
	
	mov	eax,	0
	mov	esp,	ebp
	pop	ebp
	ret