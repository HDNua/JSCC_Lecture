#include "CIL.h"

STRING sNewLine = "\n"; // ���� ���ڸ� �����ϱ� ���� ���� ���ڿ��Դϴ�.
STRING sResult = "RESULT: ";

PROC(main) // main ���ν����� ���ǰ� ���۵Ǵ� �����Դϴ�.

// ���� 0�� ����մϴ�.
PUSH(0)
INVOKE(print_int)

// ��� ȭ�鿡 ���� ���ڸ� �����մϴ�.
PUSH(sNewLine)
INVOKE(print_str)

// ���ڿ� "RESULT: "�� ����մϴ�. (���� ���ڰ� ���Ե��� �ʽ��ϴ�!)
PUSH(sResult)
INVOKE(print_str)

// �غ�� ���� a�� ������ �����մϴ�.
MOVL(a, 100)

// a�� ����� ������ ����մϴ�.
PUSH(a)
INVOKE(print_int)

// ��� ȭ�鿡 ���� ���ڸ� �����մϴ�.
PUSH(sNewLine)
INVOKE(print_str)

ENDP // ���ν����� ���Ǹ� ��Ĩ�ϴ�.