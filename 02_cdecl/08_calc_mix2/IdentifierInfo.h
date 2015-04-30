#ifndef __IDENTIFIER_H__
#define __IDENTIFIER_H__

#include "common.h"
#include <string>

class IdentifierInfo {
    std::string _name; // 식별자의 이름을 저장하는 변수
    std::string _datatype; // 자료형을 저장하는 변수
    std::string _value; // 값을 저장하는 변수
public:
    IdentifierInfo();
    IdentifierInfo(
        const std::string &name,
        const std::string &datatype,
        const std::string &value = "");

    std::string &name(); // 식별자의 이름을 반환합니다.
    const std::string &name() const; // 식별자의 이름을 반환합니다.
    std::string &datatype(); // 자료형을 반환합니다.
    const std::string &datatype() const; // 자료형을 반환합니다.
    std::string &value(); // 값을 반환합니다.
    const std::string &value() const; // 값을 반환합니다.
    void set_name(const std::string &name); // 식별자의 이름을 설정합니다.
    void set_datatype(const std::string &datatype); // 자료형을 설정합니다.
    void set_value(const std::string &value); // 값을 설정합니다.
};

#endif