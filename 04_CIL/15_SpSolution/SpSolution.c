#include "CIL.h"

PROC(main)

PUSH(10)
INVOKE(print_int)
ADD(sp, 4) // 넘긴 인자의 크기만큼 스택 포인터에 더한다

PUSH(20)
INVOKE(print_int)
ADD(sp, 4) // 넘긴 인자의 크기만큼 스택 포인터에 더한다

ENDP