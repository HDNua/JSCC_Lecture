#include "CIL.h"
STRING sNewLine = "\n"; // ���� ���ڸ� �����ϱ� ���� ���� ���ڿ��Դϴ�.

PROC(main) // main ���ν����� ���ǰ� ���۵Ǵ� �����Դϴ�.

// �غ�� ���� a�� 10�� �����ϰ� a�� ����մϴ�.
MOVL(a, 10) // a = 10

// a�� ����մϴ�.
PUSH(a)
INVOKE(print_int)

// ���� ���ڸ� �����մϴ�.
PUSH(sNewLine)
INVOKE(print_str)

// ���� a�� 10�� ���ϰ� a�� ����մϴ�.
ADD(a, 10) // a = 10

// a�� ����մϴ�.
PUSH(a)
INVOKE(print_int)

// ���� ���ڸ� �����մϴ�.
PUSH(sNewLine)
INVOKE(print_str)

// �غ�� ���� b�� 14�� �����ϰ� a���� b�� ���ϴ�.
MOVL(b, 14) // b = 14
SUB(a, b) // a -= b

// a�� ����մϴ�.
PUSH(a)
INVOKE(print_int)

ENDP // ���ν����� ���Ǹ� ��Ĩ�ϴ�.