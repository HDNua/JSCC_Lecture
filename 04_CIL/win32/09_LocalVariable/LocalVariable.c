#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// sp는 현재 메모리의 위치를 표시하는 기본 변수입니다.
// sp의 값을 정수로 출력하고 개행합니다.
PUSH(sp)
INVOKE(print_int)
PUSH(sNewLine)
INVOKE(print_str)

// sp 기본 변수의 값을 4만큼 뺍니다.
// sp -= 4;
// 4byte는 32bit 정수형 변수의 크기입니다.
SUB(sp, 4)

// sp가 가리키는 메모리의 주소 값을 a에 복사합니다.
// a = &m[sp];
// CIL은 자료형에 엄격하지 않습니다.
LEA(a, m + sp)

// a의 값을 주소 값으로 간주하고 해당 주소에 값을 설정합니다.
// *a = 10;
SETL(a, 10)

// sp가 가리키는 메모리의 값을 획득하여 a에 복사합니다.
GETL(a, m + sp)

// a의 값을 출력합니다.
PUSH(a)
INVOKE(print_int)

ENDP