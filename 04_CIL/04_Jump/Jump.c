#include "CIL.h"
STRING sHello = "HelloWorld\n";
STRING sNice = "NiceToMeetYou\n";
STRING sBye = "GoodBye\n";

PROC(main) // main ���ν����� ���ǰ� ���۵Ǵ� �����Դϴ�.

PUSH(sHello)
INVOKE(print_str)

JMP(label) // label ���̺�� �����մϴ�.

PUSH(sNice)
INVOKE(print_str)

label: // label ���̺��� �����Դϴ�.

PUSH(sBye)
INVOKE(print_str)

ENDP // ���ν����� ���Ǹ� ��Ĩ�ϴ�.