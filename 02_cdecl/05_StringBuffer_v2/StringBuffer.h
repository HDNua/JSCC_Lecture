#ifndef __HANDY_STRINGBUFFER_H__
#define __HANDY_STRINGBUFFER_H__

#include <string>
#include "common.h"

typedef Exception StringBufferException;

class StringBuffer {
    std::string str;
    unsigned len;
    unsigned idx;

public:
    StringBuffer(const char *s = "");
    StringBuffer(const std::string &str);
    ~StringBuffer();

    // 버퍼를 문자열로 초기화합니다.
    void init(const char *str);
    void init(const std::string &str);

    // 버퍼로부터 문자를 하나 읽습니다. 포인터가 이동합니다.
    char getc();
    // 버퍼의 포인터가 가리키는 문자를 가져옵니다. 포인터는 이동하지 않습니다.
    char peekc() const;
    // 버퍼에서 읽었던 값을 되돌립니다. 되돌릴 수 없으면 false를 반환합니다.
    bool ungetc();

    // 버퍼의 끝에 문자 또는 문자열을 추가합니다.
    void add(char c);
    void add(const char *s);
    void add(const std::string &str);

    // 버퍼가 비어있다면 true, 값을 더 읽을 수 있다면 false를 반환합니다.
    bool is_empty() const;

    // 버퍼로부터 정수를 획득합니다.
    std::string get_number();
    // 버퍼로부터 식별자를 획득합니다.
    std::string get_identifier();
    // 버퍼로부터 C 연산자를 획득합니다.
    std::string get_operator();
    // 공백이 아닌 문자가 나올 때까지 포인터를 옮깁니다.
    void trim();
    // 현재 위치 다음에 존재하는 토큰을 획득합니다.
    std::string get_token();
};

#endif