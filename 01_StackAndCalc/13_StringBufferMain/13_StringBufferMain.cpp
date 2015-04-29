#include <iostream>
#include "StringBuffer.h"
typedef std::string Exception;
int main(void) {
    try {
        StringBuffer buffer;
        buffer.init("Hello, world!");
        while (buffer.is_empty() == false) {
            std::cout << buffer.getc() << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}