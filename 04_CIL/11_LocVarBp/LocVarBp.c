#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// 4����Ʈ ���� ������ �����մϴ�. �ӽ÷� var1�̶�� �սô�.
// int var1;
// ���� var1�� bp�� �������� 4byte�Դϴ�.
SUB(sp, 4)

// var1 = 10;
// (bp-4)�� var1�� ����ŵ�ϴ�.
SETL(m + bp - 4, 10);

// 4����Ʈ ���� ������ �� �����մϴ�. �ӽ÷� var2��� �սô�.
// int var2;
// ���� var2�� bp�� �������� 8byte�Դϴ�.
// ���� var1�� bp�� �������� 4byte�Դϴ�.
SUB(sp, 4)

// var2 = 20;
// (bp-8)�� var2�� ����ŵ�ϴ�.
SETL(m + bp - 8, 20);

// sp�� �������� var1�� var2�� ���� ȹ���մϴ�.
GETL(a, m + bp - 4); // var1 ���� ȹ���մϴ�.
GETL(b, m + bp - 8); // var2 ���� ȹ���մϴ�.

ENDP