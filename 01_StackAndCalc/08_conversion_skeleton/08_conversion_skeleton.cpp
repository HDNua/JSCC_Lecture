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
// ��� �Լ�
int get_square(const char *ns); // ���ڿ��� ������ ��ȯ�ϰ� �� ������ ��ȯ
int get_mul(const char *ns1, const char *ns2); // �� ���ڿ��� ������ ��ȯ�ϰ� �� ���� ��ȯ
int get_volume(const char *x, const char *y, const char *z); // ���� ��� �� ��ȯ
// ������ ������ ���̿� ���̶簳�� �־� ����ϴ� ���α׷�
int main(void) {
    try {
        char input1[MAX_EXPR_LEN], input2[MAX_EXPR_LEN], input3[MAX_EXPR_LEN];
        std::cout << "Enter number: ";
        std::cin >> input1;
        std::cout << "Enter number: ";
        std::cin >> input2;
        std::cout << "Enter number: ";
        std::cin >> input3;
        std::cout << get_square(input1) << std::endl;
        std::cout << get_mul(input1, input2) << std::endl;
        std::cout << get_volume(input1, input2, input3) << std::endl;
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}
// ����
int get_square(const char *ns) { // ���ڿ��� ������ ��ȯ�ϰ� �� ������ ��ȯ
    /* implement it */
    return 0;
}
int get_mul(const char *ns1, const char *ns2) { // �� ���ڿ��� ������ ��ȯ�ϰ� �� ���� ��ȯ
    /* implement it */
    return 0;
}
int get_volume(const char *xs, const char *ys, const char *zs) { // ���� ��� �� ��ȯ
    /* implement it */
    return 0;
}