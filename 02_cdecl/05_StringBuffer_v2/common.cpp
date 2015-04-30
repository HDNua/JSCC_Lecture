#include "common.h"
#include <iostream>

// 기본 판별 함수입니다.
bool is_digit(char ch) { // 문자가 숫자라면 참입니다.
    return ('0' <= ch && ch <= '9'); 
}
bool is_lower(char ch) { // 소문자라면 참입니다.
    return ('a' <= ch && ch <= 'z');
}
bool is_upper(char ch) { // 대문자라면 참입니다.
    return ('A' <= ch && ch <= 'Z');
}
bool is_alpha(char ch) {  // 알파벳이라면 참입니다.
    return is_lower(ch) || is_upper(ch);
}
bool is_alnum(char ch) { // 알파벳 또는 숫자라면 참입니다.
    return is_digit(ch) || is_alpha(ch);
}
bool is_space(char ch) { // 공백이라면 참입니다.
    return (ch == ' ' || ch == '\t' || ch == '\n');
}

// 식별자로 가능한 문자인지 확인합니다.
bool is_namch(char ch) { // 식별자 문자라면 참입니다.
    return is_alnum(ch) || (ch == '_');
}
bool is_fnamch(char ch) { // 첫 식별자 문자라면 참입니다.
    return is_alpha(ch) || (ch == '_');
}

void clear_input_buffer() { // 입력받기 전에 입력 버퍼를 비웁니다.
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
