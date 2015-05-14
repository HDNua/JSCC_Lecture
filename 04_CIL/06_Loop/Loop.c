#include "CIL.h"
STRING sNewLine = "\n";
STRING sEnd = "Program end\n";

PROC(main) // main ���ν����� ���ǰ� ���۵Ǵ� �����Դϴ�.

MOVL(c, 5); // c = 5

// ������ ������ ���ϴ� ���̺��� �����մϴ�.
loop_start:

// c�� ���� 0�� ���մϴ�.
CMP(c, 0);

// c�� 0�̶�� �ݺ����� Ż���մϴ�.
JZ(loop_end)

// c�� ���� ���� ����մϴ�.
PUSH(c);
INVOKE(print_int);
PUSH(sNewLine);
INVOKE(print_str);

// c--
DEC(c);

// ������ ó������ �ǵ��ư� �ݺ����� �ٽ� �����մϴ�.
JMP(loop_start);

// ������ ���� ���ϴ� ���̺��� �����մϴ�.
loop_end:

PUSH(sEnd);
INVOKE(print_str);

ENDP // ���ν����� ���Ǹ� ��Ĩ�ϴ�.