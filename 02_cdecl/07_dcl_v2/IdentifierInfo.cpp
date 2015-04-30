#include "IdentifierInfo.h"
IdentifierInfo::IdentifierInfo() {}
IdentifierInfo::IdentifierInfo(
    const std::string &name,
    const std::string &dtype,
    const std::string &value)
    : _name(name), _datatype(dtype), _value(value) {}
// 식별자의 이름을 반환합니다.
std::string &IdentifierInfo::name() { return _name; }
const std::string &IdentifierInfo::name() const { return _name; }
// 자료형을 반환합니다.
std::string &IdentifierInfo::datatype() { return _datatype; }
const std::string &IdentifierInfo::datatype() const { return _datatype; }
// 값을 반환합니다.
std::string &IdentifierInfo::value() { return _value; }
const std::string &IdentifierInfo::value() const { return _value; }
// 식별자의 이름을 설정합니다.

// 자료형을 설정합니다.
void IdentifierInfo::set_datatype(const std::string &dtype) { _datatype = dtype; }
// 값을 설정합니다.
void IdentifierInfo::set_value(const std::string &value) { _value = value; }