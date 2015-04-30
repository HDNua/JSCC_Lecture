#ifndef __IDENTIFIER_TABLE_H__
#define __IDENTIFIER_TABLE_H__

#include "common.h"
#include <string>
#include <map>
#include "IdentifierInfo.h"

class Table {
    static Table *_instance; // �̱��� ��ü�� ����Ű�� ���� �ʵ�
    std::map<std::string, IdentifierInfo> _table; // ���� �ĺ��� ǥ ��ü

private: // tbl�� �̱��� ��ü�� ����� ���� �����ڸ� �����
    explicit Table();
    ~Table();

public:
    // tbl �̱��� ��ü�� �ν��Ͻ��� �����ɴϴ�.
    static Table *instance();
    // �ĺ��ڿ� ���� ������, ������ �Լ��Դϴ�.
    IdentifierInfo &get(const std::string &identifier);
    void set(const std::string &identifier, const IdentifierInfo &value);
};

#endif