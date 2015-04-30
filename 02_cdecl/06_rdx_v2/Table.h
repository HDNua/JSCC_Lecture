#ifndef __IDENTIFIER_TABLE_H__
#define __IDENTIFIER_TABLE_H__

#include "common.h"
#include <string>
#include <map>

class Table {
    static Table *_instance; // �̱��� ��ü�� ����Ű�� ���� �ʵ�
    std::map<std::string, std::string> _table; // ���� �ĺ��� ǥ ��ü

private: // tbl�� �̱��� ��ü�� ����� ���� �����ڸ� �����
    explicit Table();
    ~Table();

public:
    // tbl �̱��� ��ü�� �ν��Ͻ��� �����ɴϴ�.
    static Table *instance();
    // �ĺ��ڿ� ���� ������, ������ �Լ��Դϴ�.
    std::string &get(const std::string &identifier);
    void set(const std::string &identifier, const std::string &value);
};

#endif