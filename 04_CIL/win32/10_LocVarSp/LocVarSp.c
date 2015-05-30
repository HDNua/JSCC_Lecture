#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// 4바이트 지역 변수를 생성합니다. 임시로 var1이라고 합시다.
// int var1;
// 현재 var1과 sp의 오프셋은 0byte입니다.
SUB(sp, 4)

// var1 = 10;
// sp는 현재 var1을 가리킵니다.
SETL(m + sp, 10);

// 4바이트 지역 변수를 더 생성합니다. 임시로 var2라고 합시다.
// int var2;
// 현재 var2와 sp의 오프셋은 0byte입니다.
// 현재 var1과 sp의 오프셋은 4byte입니다.
SUB(sp, 4)

// var2 = 20;
// sp는 현재 var2를 가리킵니다.
SETL(m + sp, 20);

// sp를 기준으로 var1과 var2의 값을 획득합니다.
GETL(a, m + sp); // (sp)가 가리키는 값을 획득합니다.
GETL(b, m + sp + 4); // (sp+4)가 가리키는 값을 획득합니다.

ENDP