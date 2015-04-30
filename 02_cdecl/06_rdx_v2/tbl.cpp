#include "Table.h"
Table *Table::_instance = nullptr;

Table::Table() {}
Table::~Table() {}

Table *Table::instance() {
    return (_instance ? _instance : (_instance = new Table()));
}

std::string &Table::get(const std::string &identifier) {
    try {
        return _table[identifier];
    }
    catch (...) {
        throw Exception("�ĺ��ڿ� ���� ���� ������ �� �����ϴ�.");
    }
}
void Table::set(const std::string &identifier, const std::string &value) {
    _table[identifier] = value;
}