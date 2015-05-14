#include "CIL.h"

// main
PROC(main)

// get_sum2(10, 20)을 호출합니다.
PUSH(20)
PUSH(10)
INVOKE(get_sum2)

// 반환된 값을 출력합니다.
PUSH(a)
INVOKE(print_int)

ENDP

// get_sum2
PROC(get_sum2)

// d에 두 번째 인자의 값을 대입합니다.
GETL(d, m+bp+12)
// a에 첫 번째 인자의 값을 대입합니다.
GETL(a, m+bp+8)
// a += d;
ADD(a, d)
// 함수 종료 시에는 a의 값이 항상 반환됩니다.
// return a;
RETURN()

ENDP