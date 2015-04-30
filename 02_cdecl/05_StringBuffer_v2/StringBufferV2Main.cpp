#include <iostream>
#include "common.h"
#include "StringBuffer.h"
int main(void) {
    try {
        const int MAX_INPUT_SIZ = 256;
        char input[MAX_INPUT_SIZ];
        while (true) {
            clear_input_buffer();
            std::cin.getline(input, MAX_INPUT_SIZ);
            StringBuffer buffer(input);
            while (buffer.is_empty() == false) {
                std::string token = buffer.get_token(); // 토큰 획득
                std::cout << '['<< token.c_str() << ']'; // 감싸서 출력
            }
            std::cout << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        // 정수 획득 실패, 식별자 획득 실패 후
        // 연산자 획득 메서드인 get_operator에서 던진 예외를
        // main 함수에서 받는다.
        // 따라서 ex는 invalid operator가 된다.
        std::cerr << "Program ended" << std::endl;
        return 1;
    }
}