#include "CIL.h"
STRING sHelloWorld = "Hello, world!\n";

PROC(main)

// naked_proc ���ν����� ȣ���մϴ�.
CALL(naked_proc)

ENDP

// NAKED ���ν����� �����մϴ�.
PROC_NAKED(naked_proc)
PUSH(bp) // ���� ���� ���� �ּҸ� Ǫ���Ͽ� �����մϴ�.
MOVL(bp, sp) // ���� ���� �ּҸ� ���� ���� �����ͷ� ����ϴ�.

PUSH(sHelloWorld)
INVOKE(print_str)
ADD(sp, 4)

MOVL(sp, bp) // ���� ���� �����͸� ���� ���� �ּҷ� ����ϴ�.
POP(bp) // �����ߴ� ���� ���� ���� �ּҸ� �ҷ��ɴϴ�.
RET() // ���� �������� ���ư��ϴ�.
ENDP_NAKED
