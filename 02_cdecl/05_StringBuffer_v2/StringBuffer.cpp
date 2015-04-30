#include "StringBuffer.h"
#include <sstream>

StringBuffer::StringBuffer(const char *s) : str(s), idx(0) { this->len = this->str.length(); }
StringBuffer::StringBuffer(const std::string &str) : str(str), idx(0) { this->len = this->str.length(); }
StringBuffer::~StringBuffer() {}
void StringBuffer::init(const char *str) {
    this->str = str;
    this->idx = 0;
    this->len = this->str.length();
}
void StringBuffer::init(const std::string &str) {
    this->str = str;
    this->idx = 0;
    this->len = this->str.length();
}
char StringBuffer::getc() {
    if (idx >= len)
        throw StringBufferException("Buffer is empty");
    return str[idx++];
}
char StringBuffer::peekc() const {
    if (idx >= len)
        throw StringBufferException("Buffer is empty");
    return str[idx];
}
bool StringBuffer::ungetc() {
    if (idx > 0) {
        --idx;
        return true;
    }
    return false;
}
void StringBuffer::add(char c) {
    this->str += c;
}
void StringBuffer::add(const char *s) {
    this->str += s;
}
void StringBuffer::add(const std::string &str) {
    this->str += str;
}
bool StringBuffer::is_empty() const {
    return (idx >= len);
}

// 버퍼로부터 정수를 획득합니다.
std::string StringBuffer::get_number() {
    trim(); // 공백 제거
    if (is_empty()) // 버퍼에 남은 문자가 없다면 예외
        throw StringBufferException("Buffer is empty");
    else if (is_digit(str[idx]) == false) // 첫 문자가 숫자가 아니면 예외
        throw StringBufferException("invalid number");
    std::string value;
    while (is_empty() == false) {
        if (is_digit(str[idx]) == false)
            break;
        value += str[idx];
        ++idx;
    }
    return value;
}
// 버퍼로부터 식별자를 획득합니다.
std::string StringBuffer::get_identifier() {
    trim(); // 공백 제거
    if (is_empty()) // 버퍼에 남은 문자가 없다면 예외
        throw StringBufferException("Buffer is empty");
    else if (is_fnamch(str[idx]) == false)
        throw StringBufferException("invalid identifier");
    std::string identifier;
    while (is_empty() == false) {
        if (is_namch(str[idx]) == false) // 식별자 문자가 아니라면 탈출
            break;
        identifier += str[idx];
        ++idx;
    }
    return identifier;
}
// 버퍼로부터 C 연산자를 획득합니다.
std::string StringBuffer::get_operator() {
    trim();
    if (is_empty())
        throw StringBufferException("Buffer is empty");
    char ch = str[idx++]; // 현재 문자를 획득하고 포인터를 이동한다
    std::string op;
    switch (ch) {
    case '+': op = ch; break;
    case '-': op = ch; break;
    case '*': op = ch; break;
    case '/': op = ch; break;
    default: throw StringBufferException("invalid operator");
    }
    return op;
}
// 공백이 아닌 문자가 나올 때까지 포인터를 옮깁니다.
void StringBuffer::trim() {
    while (is_empty() == false) { // 버퍼에 문자가 남아있는 동안
        if (is_space(str[idx]) == false) // 공백이 아닌 문자를 발견하면
            break; // 반복문을 탈출한다
        ++idx; // 공백이면 다음 문자로 포인터를 넘긴다
    }
}
// 현재 위치 다음에 존재하는 토큰을 획득합니다.
std::string StringBuffer::get_token() {
    trim();
    if (is_empty())
        throw StringBufferException("Buffer is empty");
    char ch = str[idx];
    std::stringstream ss; // 문자열 스트림 생성
    if (is_digit(ch)) { // 정수를 발견했다면 정수 획득
        ss << get_number(); // cout 출력 스트림처럼 사용하면 된다
    }
    else if (is_fnamch(ch)) { // 식별자 문자를 발견했다면 식별자 획득
        ss << get_identifier();
    }
    else { // 이외의 경우 일단 연산자로 획득
        ss << get_operator();
    }
    return ss.str(); // 스트림에 담긴 문자열을 std::string 객체로 반환한다
}