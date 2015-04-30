#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>

// 예외 형식 Exception에 대한 임시적인 정의입니다.
typedef std::string Exception;

// 기본 판별 함수입니다.
bool is_digit(char ch); // 문자가 숫자라면 참입니다.
bool is_lower(char ch); // 소문자라면 참입니다.
bool is_upper(char ch); // 대문자라면 참입니다.
bool is_alpha(char ch); // 알파벳이라면 참입니다.
bool is_alnum(char ch); // 알파벳 또는 숫자라면 참입니다.
bool is_space(char ch); // 공백이라면 참입니다.

// 식별자로 가능한 문자인지 확인합니다.
bool is_namch(char ch); // 식별자 문자라면 참입니다.
bool is_fnamch(char ch); // 첫 식별자 문자라면 참입니다.

void clear_input_buffer(); // 입력받기 전에 입력 버퍼를 비웁니다.

#endif