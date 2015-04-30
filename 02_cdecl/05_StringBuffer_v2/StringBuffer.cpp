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

// ���۷κ��� ������ ȹ���մϴ�.
std::string StringBuffer::get_number() {
    trim(); // ���� ����
    if (is_empty()) // ���ۿ� ���� ���ڰ� ���ٸ� ����
        throw StringBufferException("Buffer is empty");
    else if (is_digit(str[idx]) == false) // ù ���ڰ� ���ڰ� �ƴϸ� ����
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
// ���۷κ��� �ĺ��ڸ� ȹ���մϴ�.
std::string StringBuffer::get_identifier() {
    trim(); // ���� ����
    if (is_empty()) // ���ۿ� ���� ���ڰ� ���ٸ� ����
        throw StringBufferException("Buffer is empty");
    else if (is_fnamch(str[idx]) == false)
        throw StringBufferException("invalid identifier");
    std::string identifier;
    while (is_empty() == false) {
        if (is_namch(str[idx]) == false) // �ĺ��� ���ڰ� �ƴ϶�� Ż��
            break;
        identifier += str[idx];
        ++idx;
    }
    return identifier;
}
// ���۷κ��� C �����ڸ� ȹ���մϴ�.
std::string StringBuffer::get_operator() {
    trim();
    if (is_empty())
        throw StringBufferException("Buffer is empty");
    char ch = str[idx++]; // ���� ���ڸ� ȹ���ϰ� �����͸� �̵��Ѵ�
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
// ������ �ƴ� ���ڰ� ���� ������ �����͸� �ű�ϴ�.
void StringBuffer::trim() {
    while (is_empty() == false) { // ���ۿ� ���ڰ� �����ִ� ����
        if (is_space(str[idx]) == false) // ������ �ƴ� ���ڸ� �߰��ϸ�
            break; // �ݺ����� Ż���Ѵ�
        ++idx; // �����̸� ���� ���ڷ� �����͸� �ѱ��
    }
}
// ���� ��ġ ������ �����ϴ� ��ū�� ȹ���մϴ�.
std::string StringBuffer::get_token() {
    trim();
    if (is_empty())
        throw StringBufferException("Buffer is empty");
    char ch = str[idx];
    std::stringstream ss; // ���ڿ� ��Ʈ�� ����
    if (is_digit(ch)) { // ������ �߰��ߴٸ� ���� ȹ��
        ss << get_number(); // cout ��� ��Ʈ��ó�� ����ϸ� �ȴ�
    }
    else if (is_fnamch(ch)) { // �ĺ��� ���ڸ� �߰��ߴٸ� �ĺ��� ȹ��
        ss << get_identifier();
    }
    else { // �̿��� ��� �ϴ� �����ڷ� ȹ��
        ss << get_operator();
    }
    return ss.str(); // ��Ʈ���� ��� ���ڿ��� std::string ��ü�� ��ȯ�Ѵ�
}