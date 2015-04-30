#ifndef __IDENTIFIER_TABLE_H__
#define __IDENTIFIER_TABLE_H__

#include "common.h"
#include <string>
#include <map>

class Table {
    static Table *_instance; // 싱글톤 객체를 가리키는 정적 필드
    std::map<std::string, std::string> _table; // 실제 식별자 표 객체

private: // tbl을 싱글톤 객체로 만들기 위해 생성자를 숨긴다
    explicit Table();
    ~Table();

public:
    // tbl 싱글톤 객체의 인스턴스를 가져옵니다.
    static Table *instance();
    // 식별자에 대한 접근자, 설정자 함수입니다.
    std::string &get(const std::string &identifier);
    void set(const std::string &identifier, const std::string &value);
};

#endif