#include "CIL.h"

BYTE m[MAX_MEMORY_LEN];
INT a, b, c, d;
INT sp = MAX_MEMORY_LEN, bp = MAX_MEMORY_LEN;
INT flag = 0;

INT ip = 0;
jmp_buf _ipArray[10];

jmp_buf _ip;
INT n;

// ���ν����� �ʱ�ȭ�մϴ�.
INT proc_init() {
    PUSH(bp);
    MOVL(bp, sp);
    return 0;
}
// ȣ�� ���ν����� �����ϱ� ���� ���ν����� �����մϴ�.
INT proc_retn() {
    MOVL(sp, bp);
    POP(bp);
    return 0;
}

// ���α׷����� �ֿܼ� ������ ����ϴ� �Լ��� �����մϴ�.
INT print_int() {
    INT num = *(INT *)(m + sizeof(INT) + sp);
    return printf("%d", (int)num);
}
// ���α׷����� �ֿܼ� ���ڿ��� ����ϴ� �Լ��� �����մϴ�.
INT print_str() {
    INT val = *(INT *)(m + sizeof(INT) + sp);
    return printf("%s", (const char *)val);
}