#include <iostream>

#include "common.h"
#include "StringBuffer.h"
#include "Table.h"
#include "dcl.h"
#include "rdx.h"
#include "IdentifierInfo.h"

const int MAX_INPUT_SIZ = 256;
static char input[MAX_INPUT_SIZ];

int main(void) {
    try {
        std::string command;
        std::string identifier, value;
        std::cout << "Usage: " << std::endl;
        std::cout << "- decl <declaration>" << std::endl;
        std::cout << "- movl <identifier> <value>" << std::endl;
        std::cout << "- calc <expression>" << std::endl;
        std::cout << "- exit" << std::endl;

        while (true) {
            clear_input_buffer();
            std::cout << "> ";
            std::cin >> command;
            if (command == "decl") {
                std::cin.ignore(1);
                std::cin.getline(input, MAX_INPUT_SIZ);
                std::vector<IdentifierInfo> decl_list = get_dcl_info(input);
                for (int i = 0, len = decl_list.size(); i < len; ++i) {
                    const IdentifierInfo &info = decl_list[i];
                    Table::instance()->set(info.name(), info);
                }
            }
            else if (command == "movl") {
                std::cin >> identifier >> value;
                if (Table::instance()->exist(identifier) == false) {
                    std::cout << "undefined identifier; define it first" << std::endl;
                    continue;
                }
                IdentifierInfo &info = Table::instance()->get(identifier);
                info.set_value(value);
            }
            else if (command == "calc") {
                std::cin.ignore(1);
                std::cin.getline(input, MAX_INPUT_SIZ);
                try {
                    std::cout << calculate(input) << std::endl;
                }
                catch (Exception &ex) {
                    std::cout << ex.c_str() << std::endl;
                }
            }
            else if (command == "exit") {
                break;
            }
            else {
                std::cout << "unknown command; try again" << std::endl;
            }
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}