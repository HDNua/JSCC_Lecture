#include "CIL.h"
PROC(main) // main 프로시저의 정의가 시작되는 지점입니다.

// a = 10, b = 20
MOVL(a, 10)
MOVL(b, 20)

// a와 b를 서로 비교하고 결과를 flag에 저장합니다.
CMP(a, b)

// a와 b의 차이가 0이 아니라면 elseif 레이블로 점프합니다.
JNZ(lbl_elseif)

// elseif 레이블로 점프하지 않으면 a = 30을 수행한 후
MOVL(a, 30)
// endif 레이블로 점프합니다.
JMP(lbl_endif)

// elseif 레이블로 점프했다면
lbl_elseif:
// a = 40을 수행합니다.
MOVL(a, 40);

lbl_endif:
PUSH(a)
INVOKE(print_int)

ENDP // 프로시저의 정의를 마칩니다.
