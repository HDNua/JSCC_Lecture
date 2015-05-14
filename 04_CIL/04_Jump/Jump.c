#include "CIL.h"
STRING sHello = "HelloWorld\n";
STRING sNice = "NiceToMeetYou\n";
STRING sBye = "GoodBye\n";

PROC(main) // main 프로시저의 정의가 시작되는 지점입니다.

PUSH(sHello)
INVOKE(print_str)

JMP(label) // label 레이블로 점프합니다.

PUSH(sNice)
INVOKE(print_str)

label: // label 레이블의 정의입니다.

PUSH(sBye)
INVOKE(print_str)

ENDP // 프로시저의 정의를 마칩니다.