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
                std::string token = buffer.get_token(); // ��ū ȹ��
                std::cout << '['<< token.c_str() << ']'; // ���μ� ���
            }
            std::cout << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        // ���� ȹ�� ����, �ĺ��� ȹ�� ���� ��
        // ������ ȹ�� �޼����� get_operator���� ���� ���ܸ�
        // main �Լ����� �޴´�.
        // ���� ex�� invalid operator�� �ȴ�.
        std::cerr << "Program ended" << std::endl;
        return 1;
    }
}