#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// 4����Ʈ ���� ������ �����մϴ�. �ӽ÷� var1�̶�� �սô�.
// int var1;
// ���� var1�� sp�� �������� 0byte�Դϴ�.
SUB(sp, 4)

// var1 = 10;
// sp�� ���� var1�� ����ŵ�ϴ�.
SETL(m + sp, 10);

// 4����Ʈ ���� ������ �� �����մϴ�. �ӽ÷� var2��� �սô�.
// int var2;
// ���� var2�� sp�� �������� 0byte�Դϴ�.
// ���� var1�� sp�� �������� 4byte�Դϴ�.
SUB(sp, 4)

// var2 = 20;
// sp�� ���� var2�� ����ŵ�ϴ�.
SETL(m + sp, 20);

// sp�� �������� var1�� var2�� ���� ȹ���մϴ�.
GETL(a, m + sp); // (sp)�� ����Ű�� ���� ȹ���մϴ�.
GETL(b, m + sp + 4); // (sp+4)�� ����Ű�� ���� ȹ���մϴ�.

ENDP