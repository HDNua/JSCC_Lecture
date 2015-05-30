#include "CIL.h"

STRING sHelloWorld = "Hello, world!"; // 프로그램에 사용할 문자열을 정의합니다.

PROC(main) // main 프로시저의 시작 지점입니다. PROC은 procedure의 줄임말입니다.

PUSH(sHelloWorld) // 콘솔에 문자열을 출력하기 위해 인자를 저장합니다.
INVOKE(print_str) // 콘솔에 문자열을 출력하는 프로시저를 호출합니다.

ENDP // 프로시저의 정의가 종료되는 지점입니다.