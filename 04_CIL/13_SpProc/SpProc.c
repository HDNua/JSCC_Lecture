#include "CIL.h"

// main
PROC(main)

// get_sum2(10, 20)�� ȣ���մϴ�.
PUSH(20)
PUSH(10)
INVOKE(get_sum2)

// ��ȯ�� ���� ����մϴ�.
PUSH(a)
INVOKE(print_int)

ENDP

// get_sum2
PROC(get_sum2)

// d�� �� ��° ������ ���� �����մϴ�.
GETL(d, m+bp+12)
// a�� ù ��° ������ ���� �����մϴ�.
GETL(a, m+bp+8)
// a += d;
ADD(a, d)
// �Լ� ���� �ÿ��� a�� ���� �׻� ��ȯ�˴ϴ�.
// return a;
RETURN()

ENDP