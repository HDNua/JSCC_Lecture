#include "CIL.h"

BYTE m[MAX_MEMORY_LEN];
DWORD a, b, c, d;
DWORD sp = MAX_MEMORY_LEN, bp = MAX_MEMORY_LEN;
DWORD flag = 0;

DWORD ip;
jmp_buf _ip;
DWORD n;

// ���ν����� �ʱ�ȭ�մϴ�.
int proc_init() {
    PUSH(bp);
    MOVL(bp, sp);
    return 0;
}
// ȣ�� ���ν����� �����ϱ� ���� ���ν����� �����մϴ�.
int proc_retn() {
    MOVL(sp, bp);
    POP(bp);
    return 0;
}

// ���α׷����� �ֿܼ� ������ ����ϴ� �Լ��� �����մϴ�.
int print_int() {
    int num = *(int *)(m + sizeof(DWORD) + sp);
    return printf("%d", num);
}
// ���α׷����� �ֿܼ� ���ڿ��� ����ϴ� �Լ��� �����մϴ�.
int print_str() {
    int val = *(int *)(m + sizeof(DWORD) + sp);
    return printf("%s", (const char *)val);
}