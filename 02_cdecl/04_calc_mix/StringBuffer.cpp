#include "StringBuffer.h"
#include <string>
typedef std::string Exception;
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
    if (idx >= len) {
        throw Exception("Buffer is empty");
    }
    return str[idx++];
}
char StringBuffer::peekc() const {
    if (idx >= len) {
        throw Exception("Buffer is empty");
    }
    return str[idx];
}
bool StringBuffer::ungetc() {
    if (idx > 0) {
        --idx;
        return true;
    }
    else {
        return false;
    }
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