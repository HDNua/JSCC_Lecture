#include "CIL.h"
STRING sHelloWorld = "Hello, world!\n";

PROC(main)

// naked_proc 프로시저를 호출합니다.
CALL(naked_proc)

ENDP

// NAKED 프로시저를 정의합니다.
PROC_NAKED(naked_proc)
PUSH(bp) // 이전 스택 시작 주소를 푸시하여 보관합니다.
MOVL(bp, sp) // 스택 시작 주소를 현재 스택 포인터로 맞춥니다.

PUSH(sHelloWorld)
INVOKE(print_str)
ADD(sp, 4)

MOVL(sp, bp) // 현재 스택 포인터를 스택 시작 주소로 맞춥니다.
POP(bp) // 보관했던 이전 스택 시작 주소를 불러옵니다.
RET() // 복귀 지점으로 돌아갑니다.
ENDP_NAKED
