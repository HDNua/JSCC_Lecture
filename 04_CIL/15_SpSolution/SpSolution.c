#include "CIL.h"

PROC(main)

PUSH(10)
INVOKE(print_int)
ADD(sp, 4) // �ѱ� ������ ũ�⸸ŭ ���� �����Ϳ� ���Ѵ�

PUSH(20)
INVOKE(print_int)
ADD(sp, 4) // �ѱ� ������ ũ�⸸ŭ ���� �����Ϳ� ���Ѵ�

ENDP