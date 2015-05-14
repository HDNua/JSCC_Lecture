#ifndef __C_INTERNAL_LANGUAGE_H__
#define __C_INTERNAL_LANGUAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

// 프로그램에서 사용할 문자열에 대한 형식을 정의합니다.
typedef const char *STRING;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

// 프로그램에서 사용할 내부 프로시저의 형식을 정의합니다.
#define PROTO(proc)     static int proc();
// 프로그램에서 사용할 외부 프로시저의 형식을 정의합니다.
#define EXTERN(proc)    int proc();

// 프로시저를 초기화합니다.
int proc_init();
// 호출 프로시저로 복귀하기 전에 프로시저를 정리합니다.
int proc_retn();

// 프로그램에서 콘솔에 정수를 출력하는 함수를 정의합니다.
int print_int();
// 프로그램에서 콘솔에 문자열을 출력하는 함수를 정의합니다.
int print_str();

#define MAX_MEMORY_LEN  100
extern BYTE m[MAX_MEMORY_LEN];
extern DWORD a, b, c, d;
extern DWORD sp, bp;

extern DWORD flag;
enum FLAG {
    FLAG_SIGNED = 1,
    FLAG_ZERO = 1 << 2
};

// 프로시저의 시작 지점을 정의합니다.
#define PROC(proc_name)         int proc_name() { proc_init();
// 프로시저의 종료 지점을 정의합니다.
#define ENDP                    proc_retn(); return 0; }

#define PUSH(param)             { \
    DWORD *p; \
    sp -= 4; \
    p = (DWORD *)(m + sp); \
    *p = (DWORD)(param); \
}
#define POP(param)              { \
    DWORD *p; \
    p = (DWORD *)(m + sp); \
    sp += 4; \
    (param) = *p; \
                                            }

#define MOVL(dst, src)          { (dst) = (DWORD)(src); };
#define ADD(dst, src)           { (dst) += (DWORD)(src); }
#define SUB(dst, src)           { (dst) -= (DWORD)(src); }
#define MUL(dst, src)           { (dst) *= (DWORD)(src); }
#define DIV(dst, src)           { (dst) /= (DWORD)(src); }

#define JMP(lbl)                { goto lbl; }

#define CMP(p1, p2)             { \
    flag |= ((p1 == p2) ? FLAG_ZERO : ~FLAG_ZERO); \
                                            }
#define JZ(lbl)                 if (flag & FLAG_ZERO) { goto lbl; }
#define JNZ(lbl)                if (~flag & FLAG_ZERO) { goto lbl; }

#define INC(param)              { ++(param); }
#define DEC(param)              { --(param); }

#define LEA(dst, src)           { (dst) = (DWORD)(m + src); }
#define SETL(dst, src)          { *(DWORD *)(dst) = (src); }
#define GETL(dst, src)          { (dst) = *(DWORD *)(m + src); }

#define _CALL(proc)              { \
    extern DWORD ip; \
    extern jmp_buf _ip; \
    setjmp(_ip); \
    ip = (DWORD)_ip[0]; \
    PUSH(ip); \
    proc(); \
    }
#define INVOKE(proc)            { \
    extern DWORD ip; \
    extern jmp_buf _ip; \
    extern DWORD n; \
    setjmp(_ip); \
    ip = (DWORD)_ip[0]; \
    PUSH(ip); \
    proc(); \
    POP(n); \
}
#define RET() { \
    return 0; \
}
#define EXIT()                  { exit(a); }

#endif