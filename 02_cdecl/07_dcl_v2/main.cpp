#include <iostream>

#include "common.h"
#include "StringBuffer.h"
#include "Table.h"

int main(void) {
    try {
        int main_dcl();
        main_dcl();
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}