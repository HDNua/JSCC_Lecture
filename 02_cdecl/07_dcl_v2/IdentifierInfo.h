#ifndef __IDENTIFIER_H__
#define __IDENTIFIER_H__

#include "common.h"
#include <string>

class IdentifierInfo {
    std::string _name; // �ĺ����� �̸��� �����ϴ� ����
    std::string _datatype; // �ڷ����� �����ϴ� ����
    std::string _value; // ���� �����ϴ� ����
public:
    IdentifierInfo();
    IdentifierInfo(
        const std::string &name,
        const std::string &datatype,
        const std::string &value = "");

    std::string &name(); // �ĺ����� �̸��� ��ȯ�մϴ�.
    const std::string &name() const; // �ĺ����� �̸��� ��ȯ�մϴ�.
    std::string &datatype(); // �ڷ����� ��ȯ�մϴ�.
    const std::string &datatype() const; // �ڷ����� ��ȯ�մϴ�.
    std::string &value(); // ���� ��ȯ�մϴ�.
    const std::string &value() const; // ���� ��ȯ�մϴ�.
    void set_name(const std::string &name); // �ĺ����� �̸��� �����մϴ�.
    void set_datatype(const std::string &datatype); // �ڷ����� �����մϴ�.
    void set_value(const std::string &value); // ���� �����մϴ�.
};

#endif