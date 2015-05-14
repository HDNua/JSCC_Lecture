#include "CIL.h"
PROC(main) // main ���ν����� ���ǰ� ���۵Ǵ� �����Դϴ�.

// a = 10, b = 20
MOVL(a, 10)
MOVL(b, 20)

// a�� b�� ���� ���ϰ� ����� flag�� �����մϴ�.
CMP(a, b)

// a�� b�� ���̰� 0�� �ƴ϶�� elseif ���̺�� �����մϴ�.
JNZ(lbl_elseif)

// elseif ���̺�� �������� ������ a = 30�� ������ ��
MOVL(a, 30)
// endif ���̺�� �����մϴ�.
JMP(lbl_endif)

// elseif ���̺�� �����ߴٸ�
lbl_elseif:
// a = 40�� �����մϴ�.
MOVL(a, 40);

lbl_endif:
PUSH(a)
INVOKE(print_int)

ENDP // ���ν����� ���Ǹ� ��Ĩ�ϴ�.