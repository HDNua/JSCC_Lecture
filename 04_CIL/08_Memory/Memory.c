#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// 기본 변수 a를 8로 초기화합니다.
MOVL(a, 8) // a = 8

// 정수를 출력하고 개행합니다.
PUSH(a)
INVOKE(print_int)
PUSH(sNewLine)
INVOKE(print_str)

// 메모리 10번지에 값을 설정합니다.
// *(int *)(m[10]) = 20;
SETL(m + 10, 20);

// 메모리 10번지에서 값을 획득하여 a에 저장합니다.
// a = *(int *)(m[10]);
GETL(a, m + 10);

// 획득한 값을 출력하여 올바른지 확인합니다.
PUSH(a)
INVOKE(print_int)

ENDP