#include "IdentifierInfo.h"
IdentifierInfo::IdentifierInfo() {}
IdentifierInfo::IdentifierInfo(
    const std::string &name,
    const std::string &dtype,
    const std::string &value)
    : _name(name), _datatype(dtype), _value(value) {}
// �ĺ����� �̸��� ��ȯ�մϴ�.
std::string &IdentifierInfo::name() { return _name; }
const std::string &IdentifierInfo::name() const { return _name; }
// �ڷ����� ��ȯ�մϴ�.
std::string &IdentifierInfo::datatype() { return _datatype; }
const std::string &IdentifierInfo::datatype() const { return _datatype; }
// ���� ��ȯ�մϴ�.
std::string &IdentifierInfo::value() { return _value; }
const std::string &IdentifierInfo::value() const { return _value; }
// �ĺ����� �̸��� �����մϴ�.

// �ڷ����� �����մϴ�.
void IdentifierInfo::set_datatype(const std::string &dtype) { _datatype = dtype; }
// ���� �����մϴ�.
void IdentifierInfo::set_value(const std::string &value) { _value = value; }