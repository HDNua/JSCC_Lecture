#include "CIL.h"

PROC(main)

PUSH(10)
INVOKE(print_int)

PUSH(20)
INVOKE(print_int)

ENDP
