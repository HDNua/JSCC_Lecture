#include "CIL.h"
STRING sNewLine = "\n";

// main
PROC(main)

// 4바이트 지역 변수를 생성합니다. 임시로 var1이라고 합시다.
// int var1;
// 현재 var1과 bp의 오프셋은 4byte입니다.
SUB(sp, 4)

// var1 = 10;
// (bp-4)는 var1을 가리킵니다.
SETL(m + bp - 4, 10);

// 4바이트 지역 변수를 더 생성합니다. 임시로 var2라고 합시다.
// int var2;
// 현재 var2와 bp의 오프셋은 8byte입니다.
// 현재 var1과 bp의 오프셋은 4byte입니다.
SUB(sp, 4)

// var2 = 20;
// (bp-8)은 var2를 가리킵니다.
SETL(m + bp - 8, 20);

// sp를 기준으로 var1과 var2의 값을 획득합니다.
GETL(a, m + bp - 4); // var1 값을 획득합니다.
GETL(b, m + bp - 8); // var2 값을 획득합니다.

ENDP