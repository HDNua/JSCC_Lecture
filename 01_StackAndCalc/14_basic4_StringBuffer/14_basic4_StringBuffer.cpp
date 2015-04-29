#include <iostream>
#include "StringBuffer.h"
typedef std::string Exception;

inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }
int calculate(const char *expr); // �Ѱܹ��� ���� ����Ͽ� ���� ��ȯ�Ѵ�
int ascii_to_int(StringBuffer &buffer); // ���ڿ��� ������ ��ȯ�ϰ� �� ���� ��ȯ

int main(void) {
    try {
        // �Է��� ���̰� MAX_EXPR_LEN���� ū ��찡
        // �߻����� �ʴ´ٰ� �����Ѵ�
        const int MAX_EXPR_LEN = 256;
        char expression[MAX_EXPR_LEN] = "";
        int loop;
        std::cin >> loop;
        // loop ȸ����ŭ �ݺ����� �����Ѵ�
        while (loop-- > 0) {
            std::cout << "Enter expression: ";
            std::cin >> expression;
            std::cout << calculate(expression) << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}
int ascii_to_int(StringBuffer &buffer) { // ���ڿ��� ������ ��ȯ�ϰ� �� ���� ��ȯ
    int digit = 0;
    int value = 0;
    char ch;
    while (buffer.is_empty() == false) {
        if (is_digit(ch = buffer.getc()) == false) {
            buffer.ungetc(); // ���� ���� ���� ���̹Ƿ� �ǵ��� �� Ż���Ѵ�
            break;
        }
        digit = ch - '0';
        value = 10 * value + digit;
    }
    return value;
}
int calculate(const char *expr) { // �Ѱܹ��� ���� ����Ͽ� ���� ��ȯ�Ѵ�
    StringBuffer buffer(expr);
    if (is_digit(buffer.peekc()) == false) { // �Է��� ó���� ���ڰ� �ƴ϶�� ���� ó��
        throw Exception("Ÿ������ ���� �Է��Դϴ�.");
    }
    int left = ascii_to_int(buffer); // ���ʿ� ��Ÿ���� �� ȹ��
    if (buffer.is_empty()) { // �Է��� �����ٸ� ȹ���� ������ ��ȯ�ϰ� ����
        return left;
    }
    // ������ ȹ��: ��Ģ ���꿡 ���ؼ��� �ٷ�Ƿ� ������ ���̴� �ݵ�� 1
    char op = buffer.getc(); // ���ڿ� �����Ͱ� ����Ű�� �����ڸ� ȹ�� �� ������ �̵�
    int right = ascii_to_int(buffer); // �����ʿ� ��Ÿ���� �� ȹ��
    if (buffer.is_empty() == false) { // �Է��� ���� ������ �ʾҴٸ� ���� �߻�
        throw Exception("�� ���� �ǿ����ڷθ� ������ �� �ֽ��ϴ�.");
    }
    // ȹ���� ���� �����ڸ� �̿��Ͽ� ����
    int retVal = 0;
    switch (op) {
    case '+': retVal = left + right; break;
    case '-': retVal = left - right; break;
    case '*': retVal = left * right; break;
    case '/': retVal = left / right; break;
    default: throw Exception("�ùٸ� �����ڰ� �ƴմϴ�.");
    }
    return retVal;
}