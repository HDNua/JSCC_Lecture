#include "CIL.h"
STRING sNewLine = "\n";
STRING sEnd = "Program end\n";

PROC(main) // main 프로시저의 정의가 시작되는 지점입니다.

MOVL(c, 5); // c = 5

// 루프의 시작을 뜻하는 레이블을 정의합니다.
loop_start:

// c의 값을 0과 비교합니다.
CMP(c, 0);

// c가 0이라면 반복문을 탈출합니다.
JZ(loop_end)

// c의 현재 값을 출력합니다.
PUSH(c);
INVOKE(print_int);
PUSH(sNewLine);
INVOKE(print_str);

// c--
DEC(c);

// 루프의 처음으로 되돌아가 반복문을 다시 실행합니다.
JMP(loop_start);

// 루프의 끝을 뜻하는 레이블을 정의합니다.
loop_end:

PUSH(sEnd);
INVOKE(print_str);

ENDP // 프로시저의 정의를 마칩니다.
