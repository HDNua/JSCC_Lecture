#include <iostream>
typedef std::string Exception;
inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }

int calculate(const char *expr); // �Ѱܹ��� ���� ����Ͽ� ���� ��ȯ�Ѵ�
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

int ascii_to_int_adr(const char **ns_src) { // ���ڿ� �������� �ּҸ� �ѱ��
    const char *ns = *ns_src; // ���ڿ� �����Ͱ� ����Ű�� ���� ȹ���Ѵ�
    int digit = 0;
    int value = 0;
    char ch;
    for (ch = *ns; (ch = *ns) != '\0'; ++ns) {
        if (is_digit(ch) == false) {
            break;
        }
        digit = ch - '0';
        value = 10 * value + digit;
    }
    *ns_src = ns; // �м��� ������ ���ڿ� ������ ������ ���� �����Ѵ�
    return value;
}
int ascii_to_int_ref(const char *&ns) { // ���ڿ� �������� ������ �ѱ��
    int digit = 0;
    int value = 0;
    char ch;
    for (ch = *ns; (ch = *ns) != '\0'; ++ns) {
        if (is_digit(ch) == false) {
            break;
        }
        digit = ch - '0';
        value = 10 * value + digit;
    }
    return value;
}
int calculate(const char *expr) { // �Ѱܹ��� ���� ����Ͽ� ���� ��ȯ�Ѵ�
    if (is_digit(*expr) == false) { // �Է��� ó���� ���ڰ� �ƴ϶�� ���� ó��
        throw Exception("Ÿ������ ���� �Է��Դϴ�.");
    }
    int left = ascii_to_int_adr(&expr); // ���ʿ� ��Ÿ���� �� ȹ�� (�ּ�)
    if (*expr == '\0') { // �Է��� �����ٸ� ȹ���� ������ ��ȯ�ϰ� ����
        return left;
    }
    // ������ ȹ��: ��Ģ ���꿡 ���ؼ��� �ٷ�Ƿ� ������ ���̴� �ݵ�� 1
    char op = *expr++; // ���ڿ� �����Ͱ� ����Ű�� �����ڸ� ȹ�� �� ������ �̵�
    int right = ascii_to_int_ref(expr); // �����ʿ� ��Ÿ���� �� ȹ�� (����)
    if (*expr != '\0') { // �Է��� ���� ������ �ʾҴٸ� ���� �߻�
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