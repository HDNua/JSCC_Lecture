#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// �⺻ ���� a�� 8�� �ʱ�ȭ�մϴ�.
MOVL(a, 8) // a = 8

// ������ ����ϰ� �����մϴ�.
PUSH(a)
INVOKE(print_int)
PUSH(sNewLine)
INVOKE(print_str)

// �޸� 10������ ���� �����մϴ�.
// *(int *)(m[10]) = 20;
SETL(m + 10, 20);

// �޸� 10�������� ���� ȹ���Ͽ� a�� �����մϴ�.
// a = *(int *)(m[10]);
GETL(a, m + 10);

// ȹ���� ���� ����Ͽ� �ùٸ��� Ȯ���մϴ�.
PUSH(a)
INVOKE(print_int)

ENDP