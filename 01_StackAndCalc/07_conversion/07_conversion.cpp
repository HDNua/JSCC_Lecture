#include <iostream>
// ���� ����
const int MAX_EXPR_LEN = 256;
typedef std::string Exception;
// ���� �Լ�
inline void clear_input_buffer() { // �Է¹ޱ� ���� �Է� ���۸� ����
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }
inline bool is_space(char ch) { return (ch == ' ' || ch == '\t' || ch == '\n'); }
// ������ ������ ���̿� ���̶簳�� �־� ����ϴ� ���α׷�
int main(void) {
    try {
        char expression[MAX_EXPR_LEN] = "";
        std::cin >> expression;
        char ch;
        char *expr = expression;
        // ���ڿ��� ��� ���� Ž��
        for (ch = *expr; (ch = *expr) != '\0'; ++expr) {
            if (is_digit(ch)) { // ���� �߰ߵȴٸ� ���� ȹ��
                int digit = 0; // �ڸ����� �ӽ÷� ������ ����
                int value = 0; // ���������� ȹ���� ������ ������ ����
                while (is_digit(*expr)) { // ���ڸ� ȹ���ϴ� ���� value ����
                    digit = *expr++ - '0';
                    value = 10 * value + digit;
                }
                --expr; // �ݺ��� ����� �� ++expr�� ����ǹǷ� �� ĭ �ǵ�����
                std::cout << value << ' '; // ȹ���� ������ ����ϰ� �ڿ� ������ �߰�
            }
            else { // ���� �ƴ� ������ ��� ����ϰ� �������� ����
                std::cout << ch << ' ';
            }
        }
        std::cout << std::endl;
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}