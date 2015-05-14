#include "CIL.h"
STRING sHello = "Hello, procedure!";

// main
PROC(main)
// hello 프로시저를 호출합니다.
INVOKE(hello)
ENDP

// 프로시저 hello를 정의합니다.
PROC(hello)

PUSH(sHello);
INVOKE(print_str)

ENDP