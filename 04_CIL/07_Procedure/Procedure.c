#include "CIL.h"
STRING sHello = "Hello, procedure!";

// main
PROC(main)
// hello ���ν����� ȣ���մϴ�.
INVOKE(hello)
ENDP

// ���ν��� hello�� �����մϴ�.
PROC(hello)

PUSH(sHello);
INVOKE(print_str)

ENDP