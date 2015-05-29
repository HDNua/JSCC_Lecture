%include 'handy/handy.inc'

segment .data
sHelloWorld	db	'Hello, world!', 10, 0

segment .text
	global _main

_main:
	push	ebp
	mov	ebp,	esp
	
	push	sHelloWorld
	call	print_string
	add	esp,	4
	
	mov	eax,	0
	mov	esp,	ebp
	pop	ebp
	ret