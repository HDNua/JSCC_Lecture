#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// sp�� ���� �޸��� ��ġ�� ǥ���ϴ� �⺻ �����Դϴ�.
// sp�� ���� ������ ����ϰ� �����մϴ�.
PUSH(sp)
INVOKE(print_int)
PUSH(sNewLine)
INVOKE(print_str)

// sp �⺻ ������ ���� 4��ŭ ���ϴ�.
// sp -= 4;
// 4byte�� 32bit ������ ������ ũ���Դϴ�.
SUB(sp, 4)

// sp�� ����Ű�� �޸��� �ּ� ���� a�� �����մϴ�.
// a = &m[sp];
// CIL�� �ڷ����� �������� �ʽ��ϴ�.
LEA(a, m + sp)

// a�� ���� �ּ� ������ �����ϰ� �ش� �ּҿ� ���� �����մϴ�.
// *a = 10;
SETL(a, 10)

// sp�� ����Ű�� �޸��� ���� ȹ���Ͽ� a�� �����մϴ�.
GETL(a, m + sp)

// a�� ���� ����մϴ�.
PUSH(a)
INVOKE(print_int)

ENDP