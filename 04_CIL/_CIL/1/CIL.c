#include "CIL.h"

BYTE m[MAX_MEMORY_LEN];
DWORD a, b, c, d;
DWORD sp = MAX_MEMORY_LEN, bp = MAX_MEMORY_LEN;
DWORD flag = 0;

DWORD ip;
jmp_buf _ip;
DWORD n;

// 프로시저를 초기화합니다.
int proc_init() {
    PUSH(bp);
    MOVL(bp, sp);
    return 0;
}
// 호출 프로시저로 복귀하기 전에 프로시저를 정리합니다.
int proc_retn() {
    MOVL(sp, bp);
    POP(bp);
    return 0;
}

// 프로그램에서 콘솔에 정수를 출력하는 함수를 정의합니다.
int print_int() {
    int num = *(int *)(m + sizeof(DWORD) + sp);
    return printf("%d", num);
}
// 프로그램에서 콘솔에 문자열을 출력하는 함수를 정의합니다.
int print_str() {
    int val = *(int *)(m + sizeof(DWORD) + sp);
    return printf("%s", (const char *)val);
}