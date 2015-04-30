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
        throw Exception("식별자에 대한 값을 가져올 수 없습니다.");
    }
}
void Table::set(const std::string &identifier, const std::string &value) {
    _table[identifier] = value;
}