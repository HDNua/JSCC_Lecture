#include "Table.h"
Table *Table::_instance = nullptr;

Table::Table() {}
Table::~Table() {}

Table *Table::instance() {
    return (_instance ? _instance : (_instance = new Table()));
}

IdentifierInfo &Table::get(const std::string &identifier) {
    if (_table.find(identifier) == _table.end())
        throw Exception("식별자에 대한 값을 가져올 수 없습니다.");
    return _table[identifier];
}
void Table::set(const std::string &identifier, const IdentifierInfo &value) {
    _table[identifier] = value;
}

bool Table::exist(const std::string &identifier) const {
    return (_table.find(identifier) != _table.end());
}