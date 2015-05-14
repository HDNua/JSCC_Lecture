#include "CIL.h"
STRING sNewLine = "\n"; // 개행 문자를 삽입하기 위한 개행 문자열입니다.

PROC(main) // main 프로시저의 정의가 시작되는 지점입니다.

// 준비된 변수 a에 10을 대입하고 a를 출력합니다.
MOVL(a, 10) // a = 10

// a를 출력합니다.
PUSH(a)
INVOKE(print_int)

// 개행 문자를 삽입합니다.
PUSH(sNewLine)
INVOKE(print_str)

// 변수 a에 10을 더하고 a를 출력합니다.
ADD(a, 10) // a = 10

// a를 출력합니다.
PUSH(a)
INVOKE(print_int)

// 개행 문자를 삽입합니다.
PUSH(sNewLine)
INVOKE(print_str)

// 준비된 변수 b에 14를 대입하고 a에서 b를 뺍니다.
MOVL(b, 14) // b = 14
SUB(a, b) // a -= b

// a를 출력합니다.
PUSH(a)
INVOKE(print_int)

ENDP // 프로시저의 정의를 마칩니다.