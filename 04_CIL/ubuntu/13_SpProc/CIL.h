#ifndef __C_INTERMEDIATE_LANGUAGE_H__
#define __C_INTERMEDIATE_LANGUAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <memory.h>

#define SYSTEM_BIT  64

// 프로그램에서 사용할 문자열에 대한 형식을 정의합니다.
typedef const char *STRING;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long QWORD;

#if SYSTEM_BIT == 32
typedef DWORD INT;
#define REG_SIZ 4
#else
typedef QWORD INT;
#define REG_SIZ 8
#endif

// 프로그램에서 사용할 내부 프로시저의 형식을 정의합니다.
#define PROTO(proc)     static int proc();
// 프로그램에서 사용할 외부 프로시저의 형식을 정의합니다.
#define EXTERN(proc)    int proc();

// 프로시저를 초기화합니다.
INT proc_init();
// 호출 프로시저로 복귀하기 전에 프로시저를 정리합니다.
INT proc_retn();

// 프로그램에서 콘솔에 정수를 출력하는 함수를 정의합니다.
INT print_int();
// 프로그램에서 콘솔에 문자열을 출력하는 함수를 정의합니다.
INT print_str();

#define MAX_MEMORY_LEN  100
extern BYTE m[MAX_MEMORY_LEN];
extern INT a, b, c, d;
extern INT sp, bp;

extern INT flag;
enum FLAG {
    FLAG_SIGNED = 1,
    FLAG_ZERO = 1 << 2
};

// 프로시저의 시작 지점을 정의합니다.
#define PROC(proc_name)         int proc_name() { proc_init();
// 프로시저의 종료 지점을 정의합니다.
#define ENDP                    _end_proc: proc_retn(); return 0; }

#define PUSH(param)             { \
    INT *p; \
    sp -= REG_SIZ; \
    p = (INT *)(m + sp); \
    *p = (INT)(param); \
}
#define POP(param)              { \
    INT *p; \
    p = (INT *)(m + sp); \
    sp += REG_SIZ; \
    (param) = *p; \
};

#define MOVL(dst, src)          { (dst) = (INT)(src); };
#define ADD(dst, src)           { (dst) += (INT)(src); }
#define SUB(dst, src)           { (dst) -= (INT)(src); }
#define MUL(dst, src)           { (dst) *= (INT)(src); }
#define DIV(dst, src)           { (dst) /= (INT)(src); }

#define JMP(lbl)                { goto lbl; }

#define CMP(p1, p2)             { \
    flag |= ((p1 == p2) ? FLAG_ZERO : ~FLAG_ZERO); \
};
#define JZ(lbl)                 if (flag & FLAG_ZERO) { goto lbl; }
#define JNZ(lbl)                if (~flag & FLAG_ZERO) { goto lbl; }

#define INC(param)              { ++(param); }
#define DEC(param)              { --(param); }

#define LEA(dst, src)           { (dst) = (INT)(src); }
#define SETL(dst, src)          { *(INT *)(dst) = (src); }
#define GETL(dst, src)          { (dst) = *(INT *)(src); }

#define CALL(proc)              { \
    extern INT ip; \
    extern jmp_buf _ip; \
    extern jmp_buf _ipArray[]; \
    if (setjmp(_ip) == 0) { \
        memcpy(_ipArray[ip++], &_ip, sizeof(jmp_buf)); \
        PUSH(ip); \
        proc(); \
    } \
};
#define INVOKE(proc)            { \
    extern INT n; \
    CALL(proc); \
    POP(n); \
};
#define RETURN() { \
    goto _end_proc; \
}
#define RET() { \
    extern INT ip; \
    extern jmp_buf _ip; \
    extern jmp_buf _ipArray[]; \
    POP(ip); \
    memcpy(&_ip, _ipArray[ip-1], sizeof(jmp_buf)); \
    longjmp(_ip, a); \
}
#define EXIT()                  { exit(a); }

#define PROC_NAKED(proc_name)   int proc_name() {
#define ENDP_NAKED              _end_proc: return 0; }

#endif
