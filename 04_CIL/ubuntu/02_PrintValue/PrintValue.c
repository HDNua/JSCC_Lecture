#include "CIL.h"

STRING sNewLine = "\n"; // 개행 문자를 삽입하기 위한 개행 문자열입니다.
STRING sResult = "RESULT: ";

PROC(main) // main 프로시저의 정의가 시작되는 지점입니다.

// 정수 0을 출력합니다.
PUSH(0)
INVOKE(print_int)

// 출력 화면에 개행 문자를 삽입합니다.
PUSH(sNewLine)
INVOKE(print_str)

// 문자열 "RESULT: "를 출력합니다. (개행 문자가 포함되지 않습니다!)
PUSH(sResult)
INVOKE(print_str)

// 준비된 변수 a에 정수를 대입합니다.
MOVL(a, 100)

// a에 저장된 정수를 출력합니다.
PUSH(a)
INVOKE(print_int)

// 출력 화면에 개행 문자를 삽입합니다.
PUSH(sNewLine)
INVOKE(print_str)

ENDP // 프로시저의 정의를 마칩니다.
