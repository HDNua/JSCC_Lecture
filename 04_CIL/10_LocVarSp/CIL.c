#include "CIL.h"

BYTE m[MAX_MEMORY_LEN];
INT a, b, c, d;
INT sp = MAX_MEMORY_LEN, bp = MAX_MEMORY_LEN;
INT flag = 0;

INT ip = 0;
jmp_buf _ipArray[10];

jmp_buf _ip;
INT n;

// 프로시저를 초기화합니다.
INT proc_init() {
    PUSH(bp);
    MOVL(bp, sp);
    return 0;
}
// 호출 프로시저로 복귀하기 전에 프로시저를 정리합니다.
INT proc_retn() {
    MOVL(sp, bp);
    POP(bp);
    return 0;
}

// 프로그램에서 콘솔에 정수를 출력하는 함수를 정의합니다.
INT print_int() {
    INT num = *(INT *)(m + sizeof(INT) + sp);
    return printf("%d", (int)num);
}
// 프로그램에서 콘솔에 문자열을 출력하는 함수를 정의합니다.
INT print_str() {
    INT val = *(INT *)(m + sizeof(INT) + sp);
    return printf("%s", (const char *)val);
}